# ![Example spectrogram of Steg's output](steg.png)

## What is Steg?

It's a command line program written in C that converts plain text messages into .wav files, enabling you to hide messages within sound clips such as music.

## How do I use it?

Clone the repo with `git clone git@github.com:ZoeB/steg.git`, go into that directory with `cd steg`, compile the program with `make`, and run it with a message you'd like to encode, such as `./steg 'Foo'`.  Steg will create a new file, out.wav, with your message encoded in it.

There are various command line arguments available.  Run `./steg` without a message for a list of them.

## How can I read the message again?

With a spectrogram of the waveform.  There are many ways of generating a spectrogram.  As an example, I'd recommend [Spek](http://spek.cc).

## Who made it?

The bulk of the program was written by Zoë Blade.  The .wav file writing routine was written by Douglas Thain.

## What license is it released under?

It's released under the [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/) license.
