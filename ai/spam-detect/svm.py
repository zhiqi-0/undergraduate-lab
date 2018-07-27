import numpy as np
from cvxopt.solvers import qp
from cvxopt import matrix
import utils

def softsvm(traindata, trainlabel, testdata, testlabel, C, sigma=0):
    """
    input:
        traindata: 2-D np array
    """
    # get basic info
    print 'get basic info...'
    word_hash, embedding_matrix = utils.build_tdm(traindata)
    print len(embedding_matrix)
    X = np.transpose(embedding_matrix)
    y = trainlabel.reshape(len(trainlabel), 1)
    N, M = X.shape
    K = create_kernel(X, sigma)
    # calculate multipliers
    print 'calculate multipliers...'
    P = np.multiply(np.multiply(K, y), y.T)
    q = -np.ones(shape=N)
    G = np.concatenate((np.identity(N), -np.identity(N)), axis=0)
    h = np.concatenate((C * np.ones(N), np.zeros(N)))
    A = y.reshape(1, -1).astype(float)
    b = np.zeros(1)
    solution = qp(P=matrix(P), q=matrix(q), G=matrix(G), h=matrix(h), A=matrix(A), b=matrix(b))
    alpha = np.ravel(solution['x']).reshape(-1)
    # get support vector
    print 'get support vectors & calculate bias...'
    alpha[alpha < 1e-5] = 0
    w = np.dot((alpha * y.reshape(-1)).T, X).T
    sv_index = np.nonzero(alpha)[0].reshape(-1)
    beta_list = []
    for i in range(len(sv_index)):
      sv_id = sv_index[i]
      beta_list.append(getBeta(X[sv_id,:], y[sv_id,:], w))
    beta = np.average(np.array(beta_list))
    # predict
    print 'predict...'
    testmat = utils.build_tdm_from_hash(testdata, word_hash)
    testmat = np.transpose(testmat)
    ypred = (np.dot(testmat, w) + beta) > 0
    ypred = 2 * ypred - 1
    # cal SP = correct_spam_num / correct_spam_num + incorrect_spam_num
    detect_spams = testlabel[np.where(ypred == -1)[0]]
    right_detect_spam = len(np.where(detect_spams == -1)[0])
    SP = float(right_detect_spam) / len(detect_spams)
    # cal SR = correct_spam_num / Nspam
    SR = float(right_detect_spam) / len(np.where(testlabel == -1)[0])
    F = SP * SR * 2 / (SP + SR)
    return (ypred, SP, SR, F)
        
def getBeta(xi, yi, w):
      return float(1/yi - np.dot(xi.reshape(1,-1), w.reshape(-1,1)))


def create_kernel(X, sigma):
    """
    create a kernel using gaussian kernel or linear kernel
    """
    Xmat = X.reshape((len(X), 1, X.shape[1]))
    if sigma != 0:
        # RBF kernel
        minus = Xmat - np.transpose(Xmat, (1, 0, 2))
        dist = np.sum(np.square(minus), axis=2)
        kernel = np.exp(-dist / (sigma * sigma))
    else:
        # linear kernel
        kernel = Xmat * np.transpose(Xmat, (1, 0, 2))
        kernel = np.sum(kernel, axis=2)
    return kernel

if __name__ == '__main__':
    # get dataset
    hamdata, _ = utils.extract_feature('dataset/ham', min_frequency=40, max_frequency=2000)
    spamdata, _ = utils.extract_feature('dataset/spam', min_frequency=25, max_frequency=2000)
    traindata = np.append(hamdata[0 : int(len(hamdata) * 0.2)], spamdata[0 : int(len(spamdata) * 0.2)])
    trainlabel = np.array([1 for _ in range(int(len(hamdata) * 0.2))] + [-1 for _ in range(int(len(spamdata) * 0.2))], dtype='int')
    testdata = np.append(hamdata[int(len(hamdata) * 0.2):], spamdata[int(len(spamdata) * 0.2):])
    testlabel = np.array([1 for _ in range(len(hamdata) - int(len(hamdata) * 0.2))] \
                        +[-1 for _ in range(len(spamdata) - int(len(spamdata) * 0.2))], dtype='int')
    # train
    ypred, SP, SR, F = softsvm(traindata, trainlabel, testdata, testlabel, -5, 3)
    print SP, SR, F