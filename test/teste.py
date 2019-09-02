import subprocess
import sys 

dirExe    = "../build/" 
exe       = "simulation_O0" 
           
inputs = ["input1.txt", "input2.txt", "input3.txt", "input4.txt", "input5.txt", "input6.txt" , "input7.txt", "input8.txt", "input9.txt" ]
output = ["output1.txt", "output2.txt", "output3.txt", "output4.txt", "output5.txt", "output6.txt", "output7.txt", "output8.txt", "output9.txt" ]

for inp, out in zip(inputs, output):
    command = dirExe + exe + " < " + inp
    exeOut  = subprocess.check_output(command, shell=True).decode(sys.stdout.encoding)
    
    with open(out, 'r') as f:
        fileOut = f.read()
 
    fileOut  = fileOut.replace("\n", " ").split(" ")
    exeOut   = exeOut.replace("\n", " ").split(" ")[:-2]
    
    flag = True
    try:
        for v1, v2 in zip(fileOut, exeOut):
            try:
                if(abs(float(v1) - float(v2)) > 0.1):
                    flag = False
                    break    
            
            except:
                if(v1 != v2):
                    flag = False
                    break

    except:
        flag = False

    
    if(flag):
        print(inp[:-4], ": ", u'\u2713')

    else:
        print(inp[:-4], ": ", "x")