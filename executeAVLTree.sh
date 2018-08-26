#/bin/bash

REPEAT=3
#INPUT_LISTA="test/lista03.txt"
#INPUT_BUSCA="test/lista01.txt"

#INPUT_LISTA="test/fib_v2-20062017.csv"
#INPUT_BUSCA="test/lista03.txt"

#INPUT_LISTA="test/randomip_t.txt"
#INPUT_BUSCA="test/randomip_i.txt"

# $1 = Lista de IPs (Tabela de encaminhamento)
# $2 = IPs a serem buscados
# $3 = Formato do IP (se 1 = a.b.c.d senão, inteiro)
INPUT_LISTA=$1
INPUT_BUSCA=$2

#python main/main2.py -f $INPUT -o normal -times $REPEAT
#python main/main2.py -f $INPUT -o opencl -times $REPEAT -vendor intel
#python main/main2.py -f $INPUT -o opencl -times $REPEAT -vendor nvidia

 g++ AVLTree.cpp -o tree -lOpenCL -I ../../CL-1.2

#./tree kernelsBFS_AvlTree.c lista03.txt lista01.txt 30

./tree kernelsBFS_AvlTree.c $INPUT_LISTA $INPUT_BUSCA $REPEAT $3

python compileresults.py EXECParaleloGPU.txt $REPEAT
python compileresults.py EXECSequencial.txt $REPEAT
#python compileresults.py EXECNormal.txt $REPEAT

python3 generateplot.py

#python compileresults.py EXECopencl-intel.txt $REPEAT
#python compileresults.py EXECopencl-nvidia.txt $REPEAT

#python generateplot.py
