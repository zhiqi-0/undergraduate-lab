import numpy as np
import os
import re
import email

def extract_body(file_dir, handle_dir, filename):
    """
    scan original dataset and get email body
    """
    files = os.listdir(file_dir)
    tag_remove = re.compile(r'<[^>]+>')
    # check handle_dir exists:
    if not os.path.exists(handle_dir):
        os.mkdir(handle_dir)
    # clean every file
    with open(handle_dir + '/' + filename, 'w') as hf:
        for file in files:
            if not os.path.isdir(file):
                with open(file_dir + '/' + file) as f:
                    b = email.message_from_string(f.read())
                    body = handle_payload(b, tag_remove)
                    # clean data
                    body = clean_string(body)
                    hf.writelines(body + '\n')

def extract_feature(filename, min_frequency=None, max_frequency=None, max_num=None):
    vocab = dict()
    vocab_size = 0
    # scan whole dataset and calculate frequency
    sentences = open(filename).readlines()
    for sentence in sentences:
        words = sentence.split()
        for word in words:
            if not vocab.has_key(word):
                vocab[word] = 1
                if min_frequency is None:
                    vocab_size += 1
            else:
                vocab[word] += 1
                if (not min_frequency is None) and vocab[word] == min_frequency:
                    vocab_size += 1
                if (not max_frequency is None) and vocab[word] == max_frequency + 1:
                    vocab_size -= 1
    # delete useless words
    deleted_key = []
    for key in vocab.keys():
        if (min_frequency is not None) and vocab[key] < min_frequency:
            deleted_key += [key]
        elif (max_frequency is not None) and vocab[key] > max_frequency:
            deleted_key += [key]
    for keys in deleted_key:
        vocab.pop(keys)
    # maintain in small size
    deleted_key = []
    if (max_num is not None) and vocab_size > max_num:
        sorted_vocab = sorted(vocab.items(), key=lambda item:item[1])
        vocab.clear()
        for k, v in sorted_vocab[0:max_num]:
            vocab[k] = v
        vocab_size = len(vocab)
    # scan again whole dataset and remove words
    for idx in range(len(sentences)):
        words = sentences[idx].split()
        delete_word = []
        for word in words:
            if word not in vocab:
                delete_word += [word]
        sentences[idx] = ' '.join(item for item in words if item not in delete_word)
    return np.asarray(sentences), vocab_size

def handle_payload(payload, tag_remove):
    body = ""
    if payload.is_multipart():
        for sub_payload in payload.get_payload():
            body += tag_remove.sub(' ', handle_payload(sub_payload, tag_remove))
        return body
    else:
        return body + tag_remove.sub(' ', payload.get_payload())

def clean_string(text):
    """
    clean string:
        remove extra space and put letter in lowercase
    input: str
    output: cleaned str
    """
    text = re.sub(r'([^\s\w]|_|[0-9])+', '', text)
    text = ' '.join(text.split())
    text = text.lower()
    return text

def build_tdm(data):
    word_hash = dict()
    entry = 0
    # first scan get words
    for sentence in data:
        words = sentence.split()
        for word in words:
            if word not in word_hash:
                word_hash[word] = entry
                entry += 1
    # sencond scan build tdm
    embedding_matrix = np.zeros((entry, len(data)))
    for idx in range(len(data)):
        words = data[idx].split()
        for word in words:
            embedding_matrix[word_hash[word]][idx] += 1.
    return word_hash, embedding_matrix

def build_tdm_from_hash(data, word_hash):
    word_size = len(word_hash)
    embedding_matrix = np.zeros((word_size, len(data)))
    for idx in range(len(data)):
        words = data[idx].split()
        for word in words:
            if word in word_hash:
                embedding_matrix[word_hash[word]][idx] += 1.
    return embedding_matrix



def embedding_lookup(word, word_hash, embedding_matrix):
    """
    This is a entry for getting embedding for a specific word
    word_hash and embedding_matrix should not be changed 
    when calling the function
    """
    if word in word_hash:
        return embedding_matrix[word_hash[word]]
    else:
        return np.zeros(len(embedding_matrix[0]))
        

if __name__ == '__main__':
    #extract_body('raw-data/easy_ham', 'dataset', 'ham')
    #extract_body('raw-data/spam', 'dataset', 'spam')
    data1, len1 = extract_feature('dataset/ham', min_frequency=40, max_frequency=2000, max_num=800)
    _, len2 = extract_feature('dataset/spam', min_frequency=25, max_frequency=2000, max_num=800)
    _, embed = build_tdm(data1)
    print len1, len2, len(embed)