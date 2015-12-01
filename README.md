# CS4280Compilers
Compilers projects for UMSL CS4280 FS2015

P0 (Tree Traversals)

P1 (Scanner Implementation and testing)

P2 (Parser Implementation and testing using Scanner)

P3 (Full LAN to ASM compiler)

Invocation: 
```
comp <file>
```
Where <file> is some file that ends in .lan (ex. comp file would compile and generate target code for file.lan). If no file is given input will be read in from keyboard line-by-line until EOF (ctrl+d on unix/linux).

Compiler will take in code written in LAN (fake language professor came up with), and generate a target ASM file that runs on
a specialized virtual machine the professor provided. (A simple single-accumulator based assembler.)

Errors can happen in 3 places:
>1. Scanner recieves a bad token
2. Parser detects a syntax error
3. During code generation if/when a semantic error is fine


LAN LANGUAGE:
```
<program>  ->      PROGRAM <var> <block> 
<block>    ->      { <var> <stats> }
<var>      ->      empty | <type> Identifier <mvars> ;
<type>     ->      INTEGER
<mvars>    ->      empty | , Identifier <mvars>
<expr>     ->      <T> + <expr> | <T> - <expr> | <T>
<T>        ->      <F> * <T> | <F> / <T> | <F>
<F>        ->      - <F> | <R>
<R>        ->      (<expr>) | Identifier | Number   
<stats>    ->      <stat>  <mStat>
<mStat>    ->      empty | <stat>  <mStat>
<stat>     ->      <in> | <out> | <block> | <if> | <loop> | <assign>
<in>       ->      SCAN Identifier ;
<out>      ->      PRINT <expr>  ;
<if>       ->      IF ( <expr> <RO> <expr>)  THEN <block>             
<loop>     ->      LOOP ( <expr> <RO> <expr> ) <block>
<assign>   ->      Identifier = <expr> .
<RO>       ->      => | =< | == |  > | <  |  !=
```
