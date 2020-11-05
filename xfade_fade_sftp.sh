#!/bin/bash
# crossfade between multiple video clips 
# fade the final video file from black at start to black at end

#Arguments are accessed inside a script using the variables $1, $2, $3, and so on. The variable $1 refers to the first argument, $2 to the second argument
#https://www.lifewire.com/pass-arguments-to-bash-script-2200571

#added code from sftpx code which i tested for border tuners
#https://github.com/antimodular/examples/tree/master/sftp_uploader

#my video folder is called video_temp and has these files in it
#04.mp4
#03.mp4
#02.mp4
#01.mp4

#call script like this 
#sh pathToThisScript videoFolderPath fileBaseName fileExtension pathToFFMEGBin

#sh /Applications/of_v0.11.0_osx_release/apps/memorial_COVID/memorial_covid/bin/data/fade_multi.sh /Users/stephanschulz/Desktop/memorial_assets/videos_temp/ /Users/stephanschulz/Desktop/memorial_assets/videos_new/ testFile_noFade .mp4 /Applications/of_v0.11.0_osx_release/apps/memorial_COVID/memorial_covid/bin/data/ffmpeg/bin/ &


#------these are the variables being passed in when calling the shell script
scrVideoPath=$1
dstVideoPath=$2
srcBaseName=$3
fileExt=$4
ffmpegBinPath=$5

echo "scrVideoPath:"$scrVideoPath
echo "dstVideoPath:"$dstVideoPath
echo "srcBaseName:"$srcBaseName
echo "fileExt:"$fileExt

#Present Work Directory
$INITIAL_DIR=pwd
#move in to directory with all the video files
cd "$scrVideoPath"

#------------------collect all files in source folder------------
#can be written to list
#list, write and probe all files in directory
yourfilenames=`cd $scrVideoPath ; ls *.mp4`

let fileAmt=0;
lastFile=""
for eachfile in $yourfilenames
do 
((fileAmt=fileAmt+1))
lastFile=$eachfile
done
echo "file amount found:"$fileAmt


#------i am having probelms where the last file is not being added to the final video
#so i am faking a 2nd last file by copying the last one
echo "lastFile:"$lastFile
filename=$(basename -- $lastFile)
echo "filename:"$filename
extension="${filename##*.}"
filename="${filename%.*}"

echo "filename:"$filename" extension:"$extension
#cp $lastFile $filename"_extra."$extension
cp $lastFile "zzz999_"$filename"."$extension

#now read the folder content again
yourfilenames=`cd $scrVideoPath ; ls *.mp4`
((fileAmt=fileAmt+1))

#------if you want to write all file names + paths in to a text file
echo "# Videos to merge" > concat.txt
for eachfile in $yourfilenames
do
echo "file '$eachfile'" >> "concat.txt"
done
echo "$scrVideoPath"concat.txt

#for eachfile in $yourfilenames
#do 
#echo $eachfile;
##if you want to write all file names + paths in to a text file
#echo "$scrVideoPath$eachfile" >> "file '$scrVideoPath'"mylist.txt;
#
##dur=$("$ffmpegBinPath"ffprobe -loglevel error -show_entries format=duration -of default=nk=1:nw=1 $scrVideoPath$eachfile)
###offset=$(bc -l <<< "$dur"-1)
##echo "duration is "$dur
#
#done

#------------------concat all files if we want a jump cut video------------
#txt file should look like this with the word file at start of each line and '' 
#file 'A.mp4'
#file 'B.mp4'
#file 'C.mp4'
#file 'D.mp4'

#echo "try concat"
#"$ffmpegBinPath"ffmpeg -safe 0 -f concat -i concat.txt -c copy $srcBaseName"_concat"$fileExt
#rm concat.txt

#------------------fade video in and out------------
#https://advancedweb.hu/generating-a-crossfaded-slideshow-video-from-images-with-ffmpeg-and-melt/
#constructing a string that will later be executed as a command
#the string has to look like this for multiple videos to be faded in to each other
#ffmpeg -i v0.mp4 -i v1.mp4 -i v2.mp4 -i v3.mp4 -i v4.mp4 -filter_complex \
#"[0]xfade=transition=fade:duration=0.5:offset=3.5[V01]; \
#[V01][1]xfade=transition=fade:duration=0.5:offset=12.1[V02]; \
#[V02][2]xfade=transition=fade:duration=0.5:offset=15.1[V03]; \
#[V03][3]xfade=transition=fade:duration=0.5:offset=22.59,format=yuv420p[video]" \
#-map "[video]" -movflags +faststart out.mp4

#my copy of ffmpeg is located in a special path
myCommand="$ffmpegBinPath"ffmpeg
#myCommand+=" -y"

#------loop through all file path+names and add them to the command----
oneLine=""
for eachfile in $yourfilenames
do
oneLine=" -i "$eachfile
myCommand+=$oneLine
dur=$("$ffmpegBinPath"ffprobe -loglevel error -show_entries format=duration -of default=nk=1:nw=1 $eachfile)
echo " -i "$eachfile" dur "$dur
done


myCommand+=" -filter_complex "
oneLine=""

index=0
accumDuration=0.0
fadeDur=0.5

#------loop through all files and create a command string ----
for eachfile in $yourfilenames
do 

#probe video file for its duration
dur=$("$ffmpegBinPath"ffprobe -loglevel error -show_entries format=duration -of default=nk=1:nw=1 $eachfile)
#dur=$(bc -l <<< "$dur"-1)
#offset2=$(bc -l <<< "$dur"-$fadeDur)
#offset=`echo $dur-$fadeDur | bc`
#echo "dur:"$dur" offset:"$offset" offset2 "$offset2

#((accumDuration=accumDuration+$offset))
#bash does not do floats well
oldAccumDur=$accumDuration
accumDuration=`echo $accumDuration+$dur | bc`

echo ""
echo "newDuration:"$oldAccumDur" + "$dur" = "$accumDuration

#accumDuration=`echo $accumDuration-$offset | bc`

#echo "clip duration: "$offset" accumDuration "$accumDuration

if (( $index == 0 )); then
#fade between 1st and 2nd video
oldAccumDur=$accumDuration
accumDuration=`echo $accumDuration-"$fadeDur" | bc`
oneLine=" \"[0]["$((index+1))"]xfade=transition=fade:duration="$fadeDur":offset="$accumDuration"[V"$((index+1))"];"
myCommand+=$oneLine 

echo $index
echo $oneLine
echo "fadeStart:"$oldAccumDur" - "$fadeDur" = "$accumDuration

elif (( $index < $fileAmt-2 )); then

oldAccumDur=$accumDuration
accumDuration=`echo $accumDuration-"$fadeDur" | bc`
#oneLine="[V"$index"][0]xfade=transition=fade:duration="$fadeDur":offset="$accumDuration"[V"$((index+1))"];"
oneLine="[V"$index"]["$((index+1))"]xfade=transition=fade:duration="$fadeDur":offset="$accumDuration"[V"$((index+1))"];"
myCommand+=$oneLine

echo $index
echo "fadeStart:"$oldAccumDur" - "$fadeDur" = "$accumDuration
echo $oneLine

elif (( $index == $fileAmt-2 )); then
#oneLine="[V"$index"][0]xfade=transition=fade:duration="$fadeDur":offset="$accumDuration",format=yuv420p[video]\""
oneLine="[V"$index"]["$((index+1))"]xfade=transition=fade:duration="$fadeDur":offset="$accumDuration",format=yuv420p[video]\""
myCommand+=$oneLine 

echo $index
echo "last accumDuration "$accumDuration
echo $oneLine

else
#last file does not need any fade instructions
echo "nothing here"
fi

#https://stackoverflow.com/questions/63553906/merging-multiple-video-files-with-ffmpeg-and-xfade-filter

((index=index+1))
done


echo "scrVideoPath:"$scrVideoPath
echo "dstVideoPath:"$dstVideoPath
echo "srcBaseName:"$srcBaseName
echo "fileExt:"$fileExt
comboPathName=$scrVideoPath$srcBaseName$fileExt
echo "comboPathName:"$comboPathName

#myCommand+=" -map \"[video]\" -movflags +faststart /Users/stephanschulz/Desktop/memorial_assets/videos_temp/testFile_noFade_final.mp4"
myCommand+=" -map \"[video]\" -movflags +faststart "$comboPathName
#myCommand+=" -loglevel debug"
echo $myCommand


#------execute command from string----
#testCommand="echo hello people"
#eval ${testCommand}
eval ${myCommand}

#------fade beginning and end of newly combined file-----
dur=$("$ffmpegBinPath"ffprobe -loglevel error -show_entries format=duration -of default=nk=1:nw=1 "$comboPathName")
offset=$(bc -l <<< "$dur"-1)

"$ffmpegBinPath"ffmpeg -i $comboPathName -vf "fade=t=in:st=0:d=2,fade=t=out:st='$offset':d=1" -c:a copy $dstVideoPath$srcBaseName$fileExt


#------delete all files from folder to be ready for next batch that gets placed here from my main app-----
yourfilenames=`cd $scrVideoPath ; ls`
#if you want to write all file names + paths in to a text file
echo "# Videos to merge" > concat.txt
for eachfile in $yourfilenames
do
rm $eachfile
done

#------------------uoload via sftpx code------------
#you need to install sshpass on your mac 
#brew install hudochenkov/sshpass/sshpass
#you also have to add the hist key. i just installed transmit from panic.com
#old info
#https://gist.github.com/arunoda/7790979
#brew install https://raw.githubusercontent.com/kadwanev/bigboybrew/master/Library/Formula/sshpass.rb

#string myScript = scriptPath+" "+password+" "+userName+"@"+IP+" "+localPath+" "+remotePath+"/fileToBeUploaded.mp4";

serverPathAndFile=/var/www/myWebsiteHere.com/html/subfolderName/videos//$srcBaseName$fileExt
#echo $serverPathAndFile

sftp_port=serverPortGoesHere
sftp_user_ip=serverUserName@your.IP.goes.here
sftp_passw="serverPasswordHere"

#cat and tr caused problems when calling this script from my main openframeworks app
#export RND=`cat /dev/urandom | env LC_CTYPE=C tr -cd 'a-f0-9' | head -c 32`
export RND=`openssl rand -hex 32`
export TMPDIR=/tmp/$RND
export FILENAME=$(basename "$serverPathAndFile")
export DSTDIR=$(dirname "$serverPathAndFile")

mkdir $TMPDIR
cp "$dstVideoPath$srcBaseName$fileExt" $TMPDIR/$FILENAME

export SSHPASS=$sftp_passw
/usr/local/bin/sshpass -e sftp -oBatchMode=no -b - -P $sftp_port $sftp_user_ip << !
lcd $TMPDIR
cd $DSTDIR
put $FILENAME
bye
!

rm $TMPDIR/$FILENAME
rmdir $TMPDIR
