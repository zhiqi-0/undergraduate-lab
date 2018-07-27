import numpy as np
import utils
import bayes
import square
import svm

#hamdata, _ = utils.extract_feature('dataset/ham', min_frequency=5)
#spamdata, _ = utils.extract_feature('dataset/spam', min_frequency=3)
hamdata, _ = utils.extract_feature('dataset/ham', min_frequency=40, max_frequency=2000, max_num=300)
spamdata, _ = utils.extract_feature('dataset/spam', min_frequency=25, max_frequency=2000, max_num=300)

def cross_validation(train_method, param_range):
    """
    5 fold cross validation
    input:
        train_method: function
        param_range: 5 numbers
    """
    hamlen = int(len(hamdata) * 0.2)
    spamlen = int(len(spamdata) * 0.2)
    for trainID in xrange(5):
        print 'trainID %d: start training...' % (trainID)

        ham_test_idx = trainID * hamlen
        spam_test_idx = trainID * spamlen
        ham_train = np.append(hamdata[0:ham_test_idx], hamdata[ham_test_idx + hamlen:])
        spam_train = np.append(spamdata[0:spam_test_idx], spamdata[spam_test_idx + spamlen:])
        ham_test = hamdata[ham_test_idx:ham_test_idx + hamlen]
        spam_test = spamdata[spam_test_idx:spam_test_idx + spamlen]
        
        traindata = np.append(ham_train, spam_train)
        testdata = np.append(ham_test, spam_test)
        trainlabel = np.array([1 for _ in range(len(ham_train))] + [-1 for _ in range(len(spam_train))], dtype='int')
        testlabel = np.array([1 for _ in range(len(ham_test))] + [-1 for _ in range(len(spam_test))], dtype='int')

        ypred, SP, SR, F = train_method(traindata, trainlabel, testdata, testlabel, param_range[trainID])

        print 'trainID: %d, SP: %f, SR: %f, F: %f' % (trainID, SP, SR, F)

if __name__ == '__main__':
    #cross_validation(bayes.nBayesClassifier, [0.2, 0.3, 0.4, 0.5, 0.6])
    #cross_validation(square.lsClassifier, [0.02, 0.1, 0.5, 1.0, 1.5])
    cross_validation(svm.softsvm, [1., 2., 3., 4., 5.0])