#/bin/bash

REPEAT=3
#INPUT_LISTA="test/lista03.txt"
#INPUT_BUSCA="test/lista01.txt"

INPUT_LISTA="test/fib_v2-20062017.csv"
INPUT_BUSCA="test/lista03.txt"


#python main/main2.py -f $INPUT -o normal -times $REPEAT
#python main/main2.py -f $INPUT -o opencl -times $REPEAT -vendor intel
#python main/main2.py -f $INPUT -o opencl -times $REPEAT -vendor nvidia

 g++ AVLTree.cpp -o tree -lOpenCL -I ../../CL-1.2

#./tree kernelsBFS_AvlTree.c lista03.txt lista01.txt 30

./tree kernelsBFS_AvlTree.c $INPUT_LISTA $INPUT_BUSCA $REPEAT

python compileresults.py EXECParaleloGPU.txt $REPEAT
python compileresults.py EXECSequencial.txt $REPEAT
python compileresults.py EXECNormal.txt $REPEAT

python3 generateplot.py

#python compileresults.py EXECopencl-intel.txt $REPEAT
#python compileresults.py EXECopencl-nvidia.txt $REPEAT

#python generateplot.py
