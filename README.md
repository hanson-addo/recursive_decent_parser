* **Author: Hanson Addo**

## Computing First and Follow sets

## Lexical Elements
* NT – nonterminals will be single character {‘A’ – ‘Z’}
* T – terminals will be a single character {‘a’ – ‘z’}
* GOES – ‘-->’ characters
* SEMI – ‘;’
* OR – ‘|’
* EOL – end of line (\n)

## Starting grammar
prod_list –>prod_list production
            | production
production –> NT GOES production_body SEMI EOL
production_body –> production_body OR rule
                | rule
rule            ->NT rule                
                 | rule
                  | EOL