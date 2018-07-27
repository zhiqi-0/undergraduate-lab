import numpy as np
import utils
import math

def nBayesClassifier(traindata, trainlabel, testdata, testlabel, threshould):
    """
    naive bayes classifier for detecting spam
    input params:
        traindata: 1-D np array with one email body per row
        trainlabel: 1-D np array, 0 denotes spam, 1 denotes ham
        testdata: same type with traindata
        testlabel: same type with testlabel
        threshould: when estimated probobility is larger than threshould,
                    assume the test email is a spam
    """
    # set up probability for each word
    # vocab[specific_word] = [prob. of spam, prob. of ham]
    vocab = dict()
    sh_num = np.array([len(trainlabel) - sum(trainlabel), sum(trainlabel)], dtype='float32')
    prsh = sh_num / len(trainlabel)
    for idx in range(len(traindata)):
        words = traindata[idx].split()
        for word in set(words):
            if word not in vocab:
                vocab[word] = np.array([0., 0,], dtype='float32')
            vocab[word][(trainlabel[idx] + 1) / 2] += 1.
    for word in vocab:
        # cal Pr(w|s), Pr(w|h)
        vocab[word] = vocab[word] / sh_num
        # cal Pr(s|w)
        mul = vocab[word] * prsh
        vocab[word] = mul[0] / sum(mul)
        #print vocab[word]
    # pred for test data
    ypred = np.array([], dtype='int')
    for sentence in testdata:
        words = sentence.split()
        ps = np.array([], dtype='float32')
        # get p1, p2, ... , pn
        for word in set(words):
            if word in vocab:
                ps = np.append(ps, vocab[word])
        # calculate p(spam) = p1*...*pn / (p1*...*pn + (1-p1)*...*(1-pn))
        if len(ps) > 0:
            p_spam = ps.prod() / (ps.prod() + (1. - ps).prod())
        else:
            p_spam = 1.
        if math.isnan(p_spam):
            p_spam = 1.
        # check threshould, determine whether a spam
        if p_spam > threshould:
            ypred = np.append(ypred, -1)
        else:
            ypred = np.append(ypred, 1)
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
    # train
    ypred, SP, SR, F = nBayesClassifier(traindata, trainlabel, testdata, testlabel, 0.2)
    print SP, SR, F