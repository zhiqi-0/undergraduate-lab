import numpy as np
import utils

def lsClassifier(traindata, trainlabel, testdata, testlabel, lamda):
    # create embedding matrix and word dict
    print 'building TDM...'
    word_hash, embedding_matrix = utils.build_tdm(traindata)
    embedding_size = len(embedding_matrix)
    # input matrix
    print 'building train data matrix...'
    b = np.expand_dims(np.ones(len(traindata)), axis=0)
    XT = np.append(b, embedding_matrix, axis=0)         # embedding_size + 1, N
    X = np.transpose(XT)
    print 'calculating optimal W...'
    W = np.dot(np.dot(np.linalg.inv(np.dot(XT, X) + lamda * np.eye(embedding_size + 1)), XT), trainlabel.reshape((len(trainlabel), 1)))
    print 'predicting...'
    # prediction
    test_embedding = utils.build_tdm_from_hash(testdata, word_hash)
    b = np.expand_dims(np.ones(len(testdata)), axis=0)
    test_mat = np.append(b, test_embedding, axis=0)
    ypred = np.sign(np.dot(np.transpose(W), test_mat))
    ypred = ypred.reshape((ypred.shape[1],))
    # cal SP = correct_spam_num / correct_spam_num + incorrect_spam_num
    detect_spams = testlabel[np.where(ypred == -1)[0]]
    right_detect_spam = len(np.where(detect_spams == -1)[0])
    SP = float(right_detect_spam) / len(detect_spams)
    # cal SR = correct_spam_num / Nspam
    SR = float(right_detect_spam) / len(np.where(testlabel == -1)[0])
    F = SP * SR * 2 / (SP + SR)
    return (ypred, SP, SR, F)


if __name__ == '__main__':
    # get dataset
    hamdata, _ = utils.extract_feature('dataset/ham', min_frequency=5)
    spamdata, _ = utils.extract_feature('dataset/spam', min_frequency=3)
    traindata = np.append(hamdata[0 : int(len(hamdata) * 0.8)], spamdata[0 : int(len(spamdata) * 0.8)])
    trainlabel = np.array([1 for _ in range(int(len(hamdata) * 0.8))] + [-1 for _ in range(int(len(spamdata) * 0.8))], dtype='int')
    testdata = np.append(hamdata[int(len(hamdata) * 0.8):], spamdata[int(len(spamdata) * 0.8):])
    testlabel = np.array([1 for _ in range(len(hamdata) - int(len(hamdata) * 0.8))] \
                        +[-1 for _ in range(len(spamdata) - int(len(spamdata) * 0.8))], dtype='int')
    ypred, SP, SR, F = lsClassifier(traindata, trainlabel, testdata, testlabel, 1.5)
    print SP, SR, F

