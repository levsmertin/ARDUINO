int i=0; 
char buffer[100]; 

//если есть данные - читаем 
if(Serial.available()){ 
delay(100); 

//загоняем прочитанное в буфер 
while( Serial.available() && i< 99) { 
buffer[i++] = Serial.read(); 
} 
buffer[i++]='\0'; 
} 
if(i>0){ 

//разбераем его на части отделенные запятой 
sscanf(buffer, "%[^','],%[^','],%s", &unitID_in, &command_in, &data_in);
} 


String ID_s = (String)unitID_in; 
String com = (String)command_in; 
String data = (String)data_in; 
int ID = ID_s.toInt(); 
switch (ID) 
{ 
case 70: 
if (com == "") 
{ 
if (!sig_on) 
Serial.println("70,0"); 
if (sig_on) 
Serial.println("70,1"); 
} 
if (com == "on") 
{ 
sign_on(); 
} 
if (com == "off") 
{ 
sign_off(); 
} 
if (com == "set_on") 
{ 
code_on = (String)data_in; 
Serial.println("70,3"); 
} 
if (com == "set_off") 
{ 
code_off = (String)data_in; 
Serial.println("70,3"); 
} 
if (com == "get_on") 
{ 
Serial.println(code_on); 
} 
if (com == "get_off") 
{ 
Serial.println(code_off); 
} 
break; 

case 100: 
h = dht.readHumidity(); 
t = dht.readTemperature(); 
if (isnan(h) || isnan(t)) 
{ 
Serial.println("100,0"); 
return; 
} 
Serial.println("100,"+(String)h+' '+(String)t); 
break; 

case 123: 
if (com.toInt() >= 0 && com.toInt() <=180) 
if (com.toInt() < 9) 
servo.write(9); 
else servo.write(com.toInt()); 
break; 
case 1: 
digitalWrite(led1, !digitalRead(led1)); 
break; 
case 2: 
digitalWrite(led2, !digitalRead(led2)); 
break; 
case 3: 
digitalWrite(led3, !digitalRead(led3)); 
break; 
case 4: 
digitalWrite(led4, !digitalRead(led4)); 
break; 
case 5: 
digitalWrite(led5, !digitalRead(led5)); 
break; 
} 
unitID_in [0] = '\0'; 
command_in [0] = '\0'; 
data_in [0] = '\0';
