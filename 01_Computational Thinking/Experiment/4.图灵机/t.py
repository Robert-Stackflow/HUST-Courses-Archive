import re
blank_symbol = " "
class Tape(object):
    def __init__(self, input=""):
        self.__tape = list(input)
    def __str__(self):
        s = ""
        # 请在此添加代码，补全函数__str__
        #-----------Begin----------
        for i in range(len(self.__tape)):
            s += self.__tape[i]
        #------------End-----------
        return s
    def __getitem__(self, index):
        # 请在此添加代码，补全函数__getitem__
        #-----------Begin----------
        if index in range(len(self.__tape)):
            return self.__tape[index]
        else:
            return blank_symbol
        #------------End-----------
    def __setitem__(self, pos, char):
        # 请在此添加代码，补全函数__setitem__
        #-----------Begin----------
        self.__tape[pos] = char
        #------------End-----------
class TuringMachine(object):
    def __init__(self,
                 tape="",
                 blank_symbol=" ",
                 tape_alphabet=["V", "C", " ", "=", "+", ";"],
                 initial_state="",
                 final_states=[],
                 transition_function={}):
        # 请在此添加代码，补全函数__init__
        #-----------Begin----------
        self.__tape = Tape(tape)
        self.__head_position = 0
        self.__blank_symbol = blank_symbol
        self.__current_state = initial_state
        self.__transition_function = transition_function
        self.__tape_alphabet = tape_alphabet
        self.__final_states = final_states
        #------------End-----------
    def show_tape(self):
        print(self.__tape)
    def step(self):
        char_under_head = self.__tape[self.__head_position]
        x = (self.__current_state, char_under_head)
        # 请在此添加代码，补全函数step
        #-----------Begin----------
        if x in self.__transition_function:
            y = self.__transition_function[x]
            #print("pos: "+ str(self.__head_position))
            print(str(x) + ":" + str(y))
            self.__tape[self.__head_position] = y[1]
            if y[2] == "R":
                self.__head_position += 1
            elif y[2] == "L":
                self.__head_position -= 1
            self.__current_state = y[0]
            return True
        else:
            return False
        #------------End-----------
    def final(self):
        # 请在此添加代码，补全函数final
        #-----------Begin----------
        if self.__current_state in self.__final_states:
            return True
        else:
            return False
        #------------End-----------
if __name__=="__main__":
    initial_state = "S1"
    transition_function = {("S1", " "): ("S1", "", "R"),
                           ("S1", "V"): ("S2", "V", "R"),
                           ("S2", " "): ("S2", "", "R"),
                           ("S2", "="): ("S3", "=", "R"),
                           ("S3", " "): ("S3", "", "R"),
                           ("S3", "C"): ("S4", "C", "R"),
                           ("S4", " "): ("S4", "", "R"),
                           ("S4", "+"): ("S5", "+", "R"),
                           ("S4", ";"): ("S7", "", "N"),
                           ("S5", " "): ("S5", "", "R"),
                           ("S5", "C"): ("S6", "C", "R"),
                           ("S6", " "): ("S6", "", "R"),
                           ("S6", ";"): ("S7", "", "N")
                           }
    final_states = ["S7"]
    for tape in [" ksd = 65 ;", " res  =78 +194 ;", "ff = rsh  + 5448 ;", "k =3*3 ;"]:
        s1 = re.sub(r'[_a-zA-Z]\w*', "V", tape)
        s2 = re.sub(r'0|[1-9]\d*', "C", s1)
        #print(Tape(s2).__tape)
        t = TuringMachine(s2, initial_state="S1",
                          final_states=final_states,
                          transition_function=transition_function)
        print("Input on Tape:")
        print(tape)
        flag = True
        while not t.final():
            if not t.step():
                print("false")
                flag = False
                break;
        if flag:
            print("Result of Turing machine calculation:")
            t.show_tape()