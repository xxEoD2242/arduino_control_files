#define str(s)

void setup() {
  Serial.begin(9600);
  while(!Serial)
  {
    ;
  }
  
  String username = USERNAME;
  Serial.print("This is the username: ");
  Serial.println(username);

  Serial.print("Goodbye!");
}

void loop() {
  // put your main code here, to run repeatedly:

}
