output_cws = open('cws_result2.txt', 'w', encoding='utf-8')
cws_label = open('cws_label.txt', 'r', encoding='utf-8')
ner_label = open('ner_label.txt', 'r', encoding='utf-8')
cws_label_lines=cws_label.readlines()
ner_label_lines=ner_label.readlines()
for i in range(len(cws_label_lines)):
    cws_label_lines[i]=cws_label_lines[i].replace('\n','')
    ner_label_lines[i]=ner_label_lines[i].replace('\n','')
    cws=cws_label_lines[i].split('   ')
    ner=ner_label_lines[i].split('   ')
    if (i==len(cws_label_lines)-1):
        next_ner=['','']
    else:
        next_ner=ner_label_lines[i+1].replace('\n','').split('   ')
    if len(next_ner)<2:
        next_ner=['','']
    if(len(cws)<2):
        print(file=output_cws)
    else:
        if ner[1]=='I' and next_ner[1]=='I':
            print(cws[0],end='',file=output_cws)
        else:
            if cws[1]=='E' or cws[1]=='S':
                print(cws[0],end=' ',file=output_cws)
            else:
                print(cws[0],end='',file=output_cws)