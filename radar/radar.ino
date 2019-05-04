const int radarTrigPin1=2;
const int radarEchoPin1=3;
const int radarTrigPin2=4;
const int radarEchoPin2=5;
char buffer[11];
double dis1=200.0;
double dis2=200.0;
char radarByteHigh1;//雷达1的高位
char radarByteHigh2;
char radarByteLow1;//雷达1的低位
char radarByteLow2;
void trigSignal(int TrigPin)
{
  buffer[0]=0xff;
  buffer[1]=0xfe;
  buffer[10]='\0';
  
  digitalWrite(TrigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW); 
}
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600,SERIAL_8N1);
  pinMode(radarTrigPin1,OUTPUT);
  pinMode(radarTrigPin2,OUTPUT);
  pinMode(radarEchoPin1,INPUT);
  pinMode(radarEchoPin2,INPUT);
}

void loop() 
{
  radarByteHigh1=0xff;
  radarByteHigh2=0xff;
  // put your main code here, to run repeatedly:
  //向两颗雷达分别发送一个10ms的高频脉冲来触发
  trigSignal(radarTrigPin1);  
  dis1=pulseIn(radarEchoPin1,HIGH)/58.3;
  
  delay(100);
  trigSignal(radarTrigPin2);
  dis2=pulseIn(radarEchoPin2,HIGH)/58.3;
  delay(100);
  //Serial.print(dis1);
  //Serial.print(" ");
  //Serial.print(dis2);
  //Serial.print("\n");
  //将测量的数据转换为相应的帧
  if(dis1>256)
  {
    int temp=(int)dis1/256.0;
    if(temp>253)
    {
      radarByteHigh1=0xfd;
    }
    radarByteLow1=(int)(dis1-temp*256.0);
  }
  else
  {
    radarByteHigh1=0x00;
    radarByteLow1=(int)dis1;
  }
  buffer[2]=radarByteHigh1;
  buffer[3]=radarByteLow1;


   if(dis2>256)
  {
    int temp2=(int)dis2/256.0;
    if(temp2>253)
    {
      radarByteHigh2=0xfd;
    }
    radarByteLow2=(int)(dis2-temp2*256.0);
  }
  else
  {
    radarByteHigh2=0x00;
    radarByteLow2=(int)dis2;
  }
  
  
  buffer[4]=radarByteHigh2;
  buffer[5]=radarByteLow2;

 
  //剩余数据位全部填0
  for(int i=6;i<10;i++)
  {
    buffer[i]=0x00;
  }
  //0x00无法发送出去，考虑到雷达本身精度不会造成影响，因此这里将0x00全部置换为0xfe
  
  for(int i=0;i<9;i++)
  {
    if(buffer[i]==0x00)
    {
      buffer[i]=0xfe;
    }
  }
  buffer[9]=0xff;
  Serial.print(buffer);
  delay(200);
}
