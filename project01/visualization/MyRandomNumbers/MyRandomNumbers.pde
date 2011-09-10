/*

 #myrandomnumber Tutorial
 blprnt@blprnt.com
 April, 2010
 
 */

//This is the Google spreadsheet manager and the id of the spreadsheet that we want to populate, along with our Google username & password
SimpleSpreadsheetManager sm;
String sUrl = "t6mq_WLV5c5uj6mUNSryBIA";
String googleUser = "twacker@mymail.mines.edu";
String googlePass = "dr.wacker";
PFont label;
  
void setup() {
  //This code happens once, right when our sketch is launched
 size(800,800);
 background(0);
 smooth();
 label = createFont("Helvetica", 24);
 // get the list of numbers from google
 int[] numbers = getNumbers();
 numsGrid(numbers,50,50,70);
};

void dots( int[] numbers){
   fill(255,40);
   noStroke();
   // numbers from the array off google
   for (int i = 0; i < numbers.length; i++){
     ellipse(numbers[i] *8, height/2, 8,8); 
   };
   // random set of numbers from the computer
   for (int i = 0; i < numbers.length; i++){
     ellipse(ceil(random(0,99)) * 8, height/2 + 20, 8,8);
   };
};

void barGraph(int[] nums, float y){
 // initate the counting array
 int[] counts = new int[100];
 for (int i = 1; i < 100; i++){
   counts[i] = 0;
 }; 
 //fill in the counting array
 for (int i = 0; i < nums.length; i++){
  counts[nums[i]] ++; 
 };
 //draw the bar graph
 for (int i = 0; i < counts.length; i++){
   colorMode(HSB);
   fill(counts[i] * 30, 255, 255);
   rect(i*8, y, 8, -counts[i] * 10);
 };
};

void colorGrid(int[] nums, float x, float y, float s){
 // initate the counting array
  int[] counts = new int[100];
  for (int i = 0; i < 100; i ++){
    counts[i] = 0;
  };
  //fill in the counting array
  for(int i = 0; i < nums.length; i ++){
    counts[nums[i]] ++;
  };
  // fill in the blocks
  pushMatrix();
  translate(x,y);
  for(int i = 0; i < counts.length; i++){
    colorMode(HSB);
    fill(counts[i] * 30, 255, 255, counts[i] * 30);
    rect((i % 10) * s, floor(i/10) * s,s,s);
  };
  popMatrix();
};

void numsGrid(int[] nums, float x, float y, float s){
 // initate the counting array
  int[] counts = new int[100];
  for (int i = 0; i < 100; i ++){
    counts[i] = 0;
  };
  //fill in the counting array
  for(int i = 0; i < nums.length; i ++){
    counts[nums[i]] ++;
  };
  // fill in the blocks
  pushMatrix();
  translate(x,y);
  for(int i = 0; i < counts.length; i++){
    colorMode(HSB);
    fill(counts[i] * 30, 255, 255, counts[i] * 30);
    textAlign(CENTER);
    textFont(label);
    textSize(s/2);
    text(i, (i % 10) *s, floor(i/10) * s);
  };
  popMatrix();
};

void draw() {

};





