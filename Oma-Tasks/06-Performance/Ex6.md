## 1
$1)$ I expect imporving the execution of other instructions to benefit the system the most as it takes up a plurality of the computers time.<br>

$2)$<br> 
Accessing memory: ${{1}\over{{0.7}+{{0.3}\over{2}}}} = 1.17$<br>

Performing multiplication: ${{1}\over{{0.8}+{{0.2}\over{2}}}} = 1.11$<br>

Executing other instructions: ${{1}\over{{0.5}+{{0.5}\over{2}}}} = 1.3$

## 2
${{1}\over{{0.6}+{{0.4}\over{x}}}} = 1.2$ $||$ $\times{{0.6}+{{0.4}\over{x}}}$<br><br>
$1=1.2({0.6}+{{0.4}\over{x}})$ $||$ $:1.2$<br><br>
${{1}\over{1.2}}=0.6+{{0.4}\over{x}}$ $||$ $-0.6$<br><br>
$({{1}\over{1.2}})-0.6={{0.4}\over{x}}$ $||$ $\times{x}$<br><br>
$x(({{1}\over{1.2}})-0.6)=0.4$ $||$ $:(({{1}\over{1.2}})-0.6)$<br><br>
$x={{0.4}\over{{{1}\over{1.2}}-0.6}}$<br><br>
$x=1.71429$

## 3
Total instuction times (number $\times$ execution time):<br>
Addition = $10 000 000 \times 2= 20000000$<br>
Multiplication = $30 000 000 \times 20 = 600000000$<br>
Memory = $35 000 000 \times 10 = 350000000$<br>
Branch = $15 000 000 \times 4 = 60000000$<br>

Instruction times as a percentage:<br>
Total instuction time: $(20 + 600 + 350 + 60)\times{10^{6}} = 1030000000$<br>
Addition = ${{20000000}\over{1030000000}}=0.019$<br>
Multiplication = ${{600000000}\over{1030000000}}=0.582$<br>
Memory = ${{350000000}\over{1030000000}}=0.339$<br>
Branch = ${{60000000}\over{1030000000}}=0.058$<br>

Speedup factor:<br>
Addition: ${{1}\over{(1-0.019)+{{0.019}\over{2}}}}=1.00959$<br>
Multiplication: ${{1}\over{(1-0.582)+{{0.582}\over{1.3}}}}=1.15514$<br>
Memory: ${{1}\over{(1-0.339)+{{0.339}\over{3}}}}=1.29199$<br>
Branch: ${{1}\over{(1-0.058)+{{0.058}\over{4}}}}=1.04548$<br>

Ranked:<br>
1: Memory<br>
2: Multiplication<br>
3: Branch<br>
4: Addition

## 4
Reduce serial portion: ${{1}\over{0.1+{{0.9}\over{8}}}}=4.7$<br>
Increase cores: ${{1}\over{0.2+{{0.8}\over{16}}}}=4$<br><br>
Choose the 10% speedup.