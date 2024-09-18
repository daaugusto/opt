# Building Opt

In order to compile opt, type the following commands:
```
cbp2make -in opt.cbp
make -f opt.cbp.mak
```

# Running Opt

C/C++ code to metaheuristics and metamodel applications.

Example run command (release mode; for debugging use `Debug` instead of `Release`):
```
./bin/Release/opt -alg SMDE -eval APM -F 0.5 -s 1 -sm LLR -smp 1 -nap 4 -opDE 0-1-2-5 -f 49 -p 50 -g 200
```

Example for bilevel version - BLDE with surrogate models
```
./bin/Release/opt -alg BLDE -eval BLDE -F 0.5 -s 1 -sm KNN -smp 3 -nap 5 -opDE 2 -f -10001 -p 20 -g 50 -pF 50 -gF 100 -s -1
```

for more information use:
```
./bin/Release/opt -h
```

## Cite this work:
- Differential Evolution with Surrogate Models: 

Krempser, E.; BERNARDINO, H. S. ; Barbosa, H. J. C. ; Lemonge, Afonso C. C. . Performance evaluation of local surrogate models in differential evolution-based optimum design of truss structures. ENGINEERING COMPUTATIONS, v. 34, p. 499-547, 2017 [link](http://dx.doi.org/10.1108/ec-06-2015-0176)

Krempser, E.. Uso de metamodelos na evolução diferencial para problemas envolvendo simulações de alto custo computacional. Phd Thesis. National Laboratory for Scientific Computing - LNCC, Brazil. 2014. [link](https://oasisbr.ibict.br/vufind/Record/LNCC_8dace5e664d31d1ff6062e8bf8d883bb) (in portuguese)

- Differential Evolution for Bilevel Optmization:

Angelo, Jaqueline S. ; Krempser, Eduardo ; Barbosa, Helio J. C. . Performance Evaluation of Local Surrogate Models in Bilevel Optimization. Lecture Notes in Computer Science. 1ed.: Springer International Publishing, 2019, v. , p. 347-359.  [link](http://dx.doi.org/10.1007/978-3-030-37599-7_29)

More about BLDE: <https://github.com/jsangelo/blde>
