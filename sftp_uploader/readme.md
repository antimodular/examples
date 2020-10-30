# upload a text file via SFTP with openframeworks and bash

This method uses this bash script:
https://stackoverflow.com/questions/16721891/single-line-sftp-from-terminal/27614291#27614291

The script requires sshpass. 
Installed sshpass on macOS:
https://gist.github.com/arunoda/7790979

Make an executable bash script:
https://www.hastac.org/blogs/joe-cutajar/2015/04/21/how-make-simple-bash-script-mac

This above script worked in the terminal.app but not when run from openframworks. I needed to make a change to the sshpass in the bash script.
How to find get the absolute path to sshpass:
https://stackoverflow.com/a/19303264

