String charactersToBinary(String str){
    String zero = "0";
    String binaryNumber = "";
    String tmp ="";
    for(int i= 0; i < str.length(); i++){
      tmp = (String(str.charAt(i), BIN));
      for(; tmp.length()<8;){
        tmp = zero + tmp;
      }
      binaryNumber = binaryNumber + tmp;
    }
    return binaryNumber;
}
