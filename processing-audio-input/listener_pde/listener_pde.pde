/**
  * LiveSpectrum
  *
  * Run an FFT on live line-in input, and plot the spectrum in dB.
  * It has a kind of decaying peak-hold as well.
  * '+' key moves the scale up (increases gain), '-' to move it down.
  * Based on http://processing.org/learning/libraries/forwardfft.html by ddf.
  *
  * 2010-01-22 Dan Ellis dpwe@ee.columbia.edu
  */
 
import ddf.minim.analysis.*;
import ddf.minim.*;
 
Minim minim;
AudioInput in;
FFT fft;
float[] peaks;

int peak_hold_time = 10;  // how long before peak decays
int[] peak_age;  // tracks how long peak has been stable, before decaying

// how wide each 'peak' band is, in fft bins
int binsperband = 10;
int peaksize; // how many individual peak bands we have (dep. binsperband)
float gain = 40; // in dB
float dB_scale = 2.0;  // pixels per dB

int buffer_size = 1024;  // also sets FFT size (frequency resolution)
float sample_rate = 44100;

int spectrum_height = 200; // determines range of dB shown
int legend_height = 20;
int spectrum_width = 512; // determines how much of spectrum we see
int legend_width = 40;

void setup()
{
  size(legend_width+spectrum_width, spectrum_height+legend_height, P2D);
  textMode(SCREEN);
  textFont(createFont("SanSerif", 12));
 
  minim = new Minim(this);
 
  in = minim.getLineIn(Minim.MONO,buffer_size,sample_rate);
 
  // create an FFT object that has a time-domain buffer 
  // the same size as line-in's sample buffer
  fft = new FFT(in.bufferSize(), in.sampleRate());
  // Tapered window important for log-domain display
  fft.window(FFT.HAMMING);

  // initialize peak-hold structures
  peaksize = 1+Math.round(fft.specSize()/binsperband);
  peaks = new float[peaksize];
  peak_age = new int[peaksize];
}


void draw()
{
  // clear window
  background(0);
  
  // perform a forward FFT on the samples in input buffer
  fft.forward(in.mix);
  
  // draw peak bars
  noStroke();
  fill(0, 128, 144); // dim cyan
  for(int i = 0; i < peaksize; ++i) { 
    int thisy = spectrum_height - Math.round(peaks[i]);
    rect(legend_width+binsperband*i, thisy, binsperband, spectrum_height-thisy);
    // update decays
    if (peak_age[i] < peak_hold_time) {
      ++peak_age[i];
    } else {
      peaks[i] -= 1.0;
      if (peaks[i] < 0) { peaks[i] = 0; }
    }
  }

  // now draw current spectrum in brighter blue
  stroke(64,192,255);
  noFill();
  for(int i = 0; i < spectrum_width; i++)  {
    // draw the line for frequency band i using dB scale
    float val = dB_scale*(20*((float)Math.log10(fft.getBand(i))) + gain);
    if (fft.getBand(i) == 0) {   val = -200;   }  // avoid log(0)
    int y = spectrum_height - Math.round(val);
    if (y > spectrum_height) { y = spectrum_height; }
    line(legend_width+i, spectrum_height, legend_width+i, y);
    // update the peak record
    // which peak bin are we in?
    int peaksi = i/binsperband;
    if (val > peaks[peaksi]) {
      peaks[peaksi] = val;
      // reset peak age counter
      peak_age[peaksi] = 0;
    }
  }
  
  // add legend
  // frequency axis
  fill(255);
  stroke(255);
  int y = spectrum_height;
  line(legend_width,y,legend_width+spectrum_width,y); // horizontal line
  // x,y address of text is immediately to the left of the middle of the letters 
  textAlign(CENTER,TOP);
  for (float freq = 0.0; freq < in.sampleRate()/2; freq += 2000.0) {
    int x = legend_width+fft.freqToIndex(freq); // which bin holds this frequency
    line(x,y,x,y+4); // tick mark
    text(Math.round(freq/1000) +"kHz", x, y+5); // add text label
  }
  
  // level axis
  int x = legend_width;
  line(x,0,x,spectrum_height); // vertictal line
  textAlign(RIGHT,CENTER);
  for (float level = -100.0; level < 100.0; level += 20.0) {
    y = spectrum_height - (int)(dB_scale * (level+gain));
    line(x,y,x-3,y);
    text((int)level+" dB",x-5,y);
  }

}

void keyReleased()
{
  // +/- used to adjust gain on the fly
  if (key == '+' || key == '=') {
    gain = gain + 5.0;
  } else if (key == '-' || key == '_') {
    gain = gain - 5.0;
  }
}
 
void stop()
{
  // always close Minim audio classes when you finish with them
  in.close();
  minim.stop();
 
  super.stop();
}

