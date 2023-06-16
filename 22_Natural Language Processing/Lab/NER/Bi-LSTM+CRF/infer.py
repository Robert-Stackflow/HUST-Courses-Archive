import torch
import pickle

if __name__ == '__main__':
    model = torch.load('save/model.pkl', map_location=torch.device('cpu'))
    output = open('ner_result.txt', 'w', encoding='utf-8')

    with open('data/ner_datasave.pkl', 'rb') as inp:
        word2id = pickle.load(inp)
        id2word = pickle.load(inp)
        tag2id = pickle.load(inp)
        id2tag = pickle.load(inp)
        x_train = pickle.load(inp)
        y_train = pickle.load(inp)
        x_test = pickle.load(inp)
        y_test = pickle.load(inp)

    with open('data/ner_test.txt', 'r', encoding='utf-8') as f:
        line_test = ''
        for test in f:
            flag = False
            test = test.strip()

            if not test:
                test = test.split(' ')
                x = torch.LongTensor(1, len(line_test))
                mask = torch.ones_like(x, dtype=torch.uint8)
                length = [len(line_test)]
                for i in range(len(line_test)):
                    if line_test[i] in word2id:
                        x[0, i] = word2id[line_test[i]]
                    else:
                        x[0, i] = len(word2id)

                predict = model.infer(x, mask, length)[0]
                for i in range(len(line_test)):
                    print(line_test[i], id2tag[predict[i]], file=output)
                    # print(test[i], end='', file=output)
                    # if id2tag[predict[i]] in ['E', 'S']:
                    #     print(' ', end='', file=output)
                print(file=output)

                line_test = ''
            
            else:
                test = test.split(' ')
                line_test += test[0]
