
int Chip_Select = 11;
int DATAIN = 10;
int Sclk = 9;
int DATAOUT = 8;

//Instruction Set
byte WREN = 0b00000110; //Set Write Enable Latch
byte WRDI = 0b00000100; //Reset Write Enable Latch
byte RDSR = 0b00000101; //Read Status Register
byte WRSR = 0b00000001; //Write Status Register
byte READ = 0b00000011; //Read Data from Memory Array
byte WRITE = 0b00000010; //Write Data to Memory Array
byte WRINC = 0b00000111; //Write Data to Secure Array
int i = 0;
unsigned int starting_address;
int h,l;
int fourhigh;
int readings[9];
int retrieve_readings[9];
void setup(){
  pinMode(Chip_Select, OUTPUT);
  pinMode(DATAIN, INPUT);
  pinMode(Sclk, OUTPUT);
  pinMode(DATAOUT, OUTPUT);
  Serial.begin(9600);
  Serial.println();
  
  Serial.flush();
  Serial.println("Done setting up..."); 
}
void loop(){
  byte aux;
  Serial.println("REGISTRER: VALUE");
  Serial.println("INCREMENTAL REGISTERS:");
  for(byte index = 0x00; index < 0x1F; index = index + 0x02){
     Serial.print(index, HEX);
     Serial.print(": ");
     aux = read_8(index);
     Serial.println(aux, HEX);
  }
  Serial.println("NOT INCREMENTAL REGISTERS:");
  for(int index = 0x20; index < 0x3FF; index = index + 0x2){
     Serial.print(index, HEX);
     Serial.print(": ");
     aux = read_8(index);
     Serial.println(aux, HEX);
  }
  Serial.println("END");
  while(1){
    
  }
  Serial.println("END");
} 

/*****************************************************/
/*functions*/
void chip_select_low(void){
  digitalWrite(Chip_Select, LOW);
  delay(3);
}
void chip_select_high(void){
  digitalWrite(Chip_Select, HIGH);
  delay(3);
}
void sclk(){
  digitalWrite(Sclk, HIGH);
  digitalWrite(Sclk, LOW);
}
/************************************************/
int read_8(int address){
  char bit;
  char inbit;
  char index;
  int value = 0;
  chip_select_low();
  send_8(READ);
  send_address(address);
  for(index = 0; index < 8; index++){
    bit = digitalRead(DATAIN);
    inbit = bit & 0x01;
    if(inbit == 1){
      value = value + (0x80>>index);
      sclk();
    }else{
      sclk();
    }
  }
  chip_select_high();
  return value;
}
/***********************************************/
void send_8(char dat){
  char bit;
  for(char index=7;index>=0;index--){
    bit = ((dat>>index) & 0x01);
    if(bit==1){
      digitalWrite(DATAOUT, HIGH);
      sclk();
    }else{
      digitalWrite(DATAOUT, LOW);
      sclk();
    }
  }
}
/******************************************************************/
void send_address(int dat){
  char bit;
  char index;
  for(index = 15;index>=0;index--){
    bit = ((dat>>index) & 0x01);
    if(bit==1){
      digitalWrite(DATAOUT, HIGH);
      sclk();
    }else{
      digitalWrite(DATAOUT, LOW);
      sclk();
    }
  }
}
/************************************************************/
