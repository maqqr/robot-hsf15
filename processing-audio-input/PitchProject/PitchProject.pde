/* R2D2 Pitch Processing
 *
 * Audio analysis for pitch extraction
 *
 * Relies on Minim audio library
 * http://code.compartmental.net/tools/minim/
 *
 * L. Anton-Canalis (info@luisanton.es)
 */

import processing.opengl.*;

import processing.serial.*;

import javax.swing.JFileChooser;

import ddf.minim.analysis.*;
import ddf.minim.effects.*;
import ddf.minim.signals.*;
import ddf.minim.*;

//PitchDetectorAutocorrelation PD; //Autocorrelation
//PitchDetectorHPS PD; //Harmonic Product Spectrum -not working yet-
PitchDetectorFFT PD; // Naive
ToneGenerator TG;
AudioSource AS;
Minim minim;

//Some arrays just to smooth output frequencies with a simple median.
float []freq_buffer = new float[10];
float []sorted;
int freq_buffer_index = 0;

long last_t = -1;
float avg_level = 0;
float last_level = 0;
String filename;
float begin_playing_time = -1;

Serial myPort;

void setup()
{
  size(1000, 500, P2D);
  minim = new Minim(this);
  minim.debugOn();

  AS = new AudioSource(minim);

  /*
  // Choose .wav file to analyze
  boolean ok = false;
  while (!ok) {
  JFileChooser chooser = new JFileChooser();
  chooser.setFileFilter(chooser.getAcceptAllFileFilter());
  int returnVal = chooser.showOpenDialog(null);
  if (returnVal == JFileChooser.APPROVE_OPTION) {
  filename = chooser.getSelectedFile().getPath();
  AS.OpenAudioFile(chooser.getSelectedFile().getPath(), 5, 512); //1024 for AMDF
  ok = true;
  }
  }
  */

  // Comment the previous block and uncomment the next line for microphone input
  AS.OpenMicrophone();

  PD = new PitchDetectorFFT();
  PD.ConfigureFFT(2048, AS.GetSampleRate());
  // PD = new PitchDetectorAutocorrelation();  //This one uses Autocorrelation
  //PD = new PitchDetectorHPS(); //This one uses Harmonit Product Spectrum -not working yet-
  PD.SetSampleRate(AS.GetSampleRate());
  AS.SetListener(PD);
  TG = new ToneGenerator (minim, AS.GetSampleRate());

  rectMode(CORNERS);
  background(0);
  fill(0);
  stroke(255);
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
}


void draw()
{
  if (begin_playing_time == -1)
    begin_playing_time = millis();

  float f = 0;
  float level = AS.GetLevel();
  long t = PD.GetTime();
  if (t == last_t) return;
  last_t = t;
  int xpos = (int)t % width;
  if (xpos >= width-1) {
    rect(0,0,width,height);
  }

  f = PD.GetFrequency();

  /*freq_buffer[freq_buffer_index] = f;
    freq_buffer_index++;
    freq_buffer_index = freq_buffer_index % freq_buffer.length;
    sorted = sort(freq_buffer);

    f = sorted[5];*/
  fill(255);
  TG.SetFrequency(f);
  TG.SetLevel(level * 10.0);

  stroke(level * 255.0 * 10.0);
  line(xpos, height, xpos, height - f / 5.0f);
  avg_level = level;
  last_level = f;

  /* TODO kirjoitetaan f ja level */
  rect(0,0,1000,250);
  fill(0);
  textSize(40);
  text(f, 50, 50);
  text(level, 50, 150);
  processInput(f, level);
  //fill(255);
  /* TODO tönnä se bt formatoinnin jälkeen 215 258 290 */
}

void processInput(float f, float level) {
  level *= 5000;
  if (level > 255) level = 255;
  if (f > 192 && f < 195) {
    textSize(40);
    text("<F:" + level + ">", 250, 50);
    myPort.write("<F:" + level + ">");
  }  
  else if (f > 213 && f < 217) {
    textSize(40);
    text("<B:" + level + ">", 250, 50);
    myPort.write("<B:" + level + ">");
  }  
  else if (f > 256 && f < 260) {
    textSize(40);
    text("<L:" + level + ">", 250, 50);
    myPort.write("<L:" + level + ">");
  }  
  else if (f > 288 && f < 292) {
    textSize(40);
    text("<R:" + level + ">", 250, 50);
    myPort.write("<R:" + level + ">");
  }  
  else myPort.write("<F:0>");
}

void stop()
{
  TG.Close();
  AS.Close();

  minim.stop();

  println("Se acabo");

  super.stop();
}

