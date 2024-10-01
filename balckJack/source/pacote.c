#include <stdio.h>
#include <stdlib.h>
#include "pacote.h" 

const char* cartas(int j, int i){
  
 // printf("valor-%d  naipe-%c\n", j, i);

  const char* aux;

   if(i == PAUS && j == 14){
     aux = APAUS;}
  
   if(i == COPAS && j== 14){
     aux = ACOPA;}

   if(i == ESPADAS && j == 14){
     aux = AESPA;}

   if(i == OUROS && j == 14){
     aux = AOURO;}
     
   if(i == PAUS && j == 13){
     aux = KPAUS;}
  
   if(i == COPAS && j == 13){
     aux = KCOPA;}

   if(i == ESPADAS && j == 13){
     aux = KESPA;}

   if(i == OUROS && j == 13){
     aux = KOURO;}
    
   if(i == PAUS && j == 12){
     aux = QPAUS;}
  
   if(i == COPAS && j == 12){
     aux = QCOPA;}

   if(i == ESPADAS && j == 12){
     aux = QESPA;}

   if(i == OUROS && j == 12){
     aux = QOURO;}
  
   if(i == PAUS && j == 11){
     aux = JPAUS;}

   if(i == COPAS && j == 11){
     return JCOPA;}

   if(i == ESPADAS && j == 11){
     aux = JESPA;}

   if(i == OUROS && j == 11){
     aux = JOURO;}

   if(i == PAUS && j == 10){
     aux = PAUS10;}
  
   if(i == COPAS && j == 10){
     aux = COPA10;}

   if(i == ESPADAS && j == 10){
     aux = ESPA10;}

   if(i == OUROS && j == 10){
     aux = OURO10;}

   if(i == PAUS && j == 9){
     aux = PAUS9;}
  
   if(i == COPAS && j == 9){
     aux = COPA9;}

   if(i == ESPADAS && j == 9){
     aux = ESPA9;}

   if(i == OUROS && j == 9){
     aux = OURO9;}

   if(i == PAUS && j == 8){
     aux = PAUS8;}
  
   if(i == COPAS && j == 8){
     aux = COPA8;}

   if(i == ESPADAS && j == 8){
     aux = ESPA8;}

   if(i == OUROS && j == 8){
     aux = OURO8;}

   if(i == PAUS && j == 7){
     aux = PAUS7;}
  
   if(i == COPAS && j == 7){
     aux = COPA7;}

   if(i == ESPADAS && j == 7){
     aux = ESPA7;}

   if(i == OUROS && j == 7){
     aux = OURO7;}

   if(i == PAUS && j == 6){
     aux = PAUS6;}
  
   if(i == COPAS && j == 6){
     aux = COPA6;}

   if(i == ESPADAS && j == 6){
     aux = ESPA6;}
  
   if(i == OUROS && j == 6){
     aux = OURO6;}
  
   if(i == PAUS && j == 5){
     aux = PAUS5;}
    
   if(i == COPAS && j == 5){
     aux = COPA5;}

   if(i == ESPADAS && j == 5){
     aux = ESPA5;}

   if(i == OUROS && j == 5){
     aux = OURO5;}

    if(i == PAUS && j == 4){
     aux = PAUS4;}
  
   if(i == COPAS && j == 4){
     aux = COPA4;}

   if(i == ESPADAS && j == 4){
     aux = ESPA4;}

   if(i == OUROS && j == 4){
     aux = OURO4;}

   if(i == PAUS && j == 3){
     aux = PAUS3;}
  
   if(i == COPAS && j == 3){
     aux = COPA3;}

   if(i == ESPADAS && j == 3){
     aux = ESPA3;}

   if(i == OUROS && j == 3){
     aux = OURO3;}

   if(i == PAUS && j == 2){
     aux = PAUS2;}
  
   if(i == COPAS && j == 2){
     aux = COPA2;}

   if(i == ESPADAS && j == 2){
     aux = ESPA2;}

   if(i == OUROS && j == 2){
     aux = OURO2;}

  if(i == PAUS && j == 1){
     aux = APAUS;}
  
   if(i == COPAS && j== 1){
     aux = ACOPA;}

   if(i == ESPADAS && j == 1){
     aux = AESPA;}

   if(i == OUROS && j == 1){
     aux = AOURO;}
  
  return   aux;

}