void Hamm_conv(int tx_data[8])
{ 
  int parity[4];
  int i=0;
  int j=0;
  int c=0;
  
     
  parity[0]=tx_data[0]^tx_data[1]^tx_data[3]^tx_data[4]^tx_data[6];
  parity[1]=tx_data[0]^tx_data[2]^tx_data[3]^tx_data[5]^tx_data[6];
  parity[2]=tx_data[1]^tx_data[2]^tx_data[3]^tx_data[7];
  parity[3]=tx_data[4]^tx_data[5]^tx_data[6]^tx_data[7];


  while(i<12)
  {
    if(i==0||i==1||i==3||i==7)
    { hamm[i] = parity[j];
      j++;
      i++;
    }
    else{
      hamm[i]=tx_data[c];
      c++;
      i++;
    }
  
  }
    
      
}
