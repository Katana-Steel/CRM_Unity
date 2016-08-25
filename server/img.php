<?
$path = "images/";
$scale = $_GET['scale'];      // tales the value of ?scale= and stores it for scaling
$w = $_GET['w'];              // takes the value of ?w= and stores it in $w
if($w == "") $w = 200;        // sets a default value if ?w= wasn't surplied
$h = $_GET['h'];              // takes the value of ?h= and stores it in $h
if($h == "") $h = 200;        // sets a default value if ?h= wasn't surplied
$file = $_GET['img'];         // get the filename from ?file=
$p = strrpos($file,".") + 1;  // get the position of the last '.'
$ext = strtolower(substr($file,$p));      // extract the extension from the filename
switch($ext) {				  // sets the type and image object acording to the extension
case 'jpeg':
case 'jpe':
case 'jpg':
$type = "jpeg";
$im = imagecreatefromjpeg($path.$file);
break;
case 'gif':
$type = "gif";
$im = imagecreatefromgif($path.$file);
break;
case 'png':
$type = "png";
$im = @imagecreatefrompng($path.$file);
imagealphablending($im, false);
imagesavealpha($im, true);
break;
default:					  // if the extention isn't a jpeg, gif, or png return a raw jpeg
header("Content-type: image/jpeg");
$out = imagecreate($w,$h);
imagejpeg($out);
exit();
}
$q = $_GET['q'];			  // gets ?q= (only used with jpeg)
if($q == "") $q = 85;		  // set a default value of q
if($q < 0)   $q = 0;		  // make sure that q is in the range of 0 and 100
if($q > 100) $q = 100;

$irw = imagesx($im);
$irh = imagesy($im);

switch($scale) {
case 'h':
$ratio = $irh/$irw;
$h = $w * $ratio;
break;
case 'w':
$ratio = $irw/$irh;
$w = $h * $ratio;
break;
}
$out = imagecreatetruecolor($w,$h);	  // the output image
// $black = imagecolorallocate($out, 0, 0, 0);
// imagecolortransparent($out,$black);
imagealphablending($out, false);
imagesavealpha($out, true);
imagecopyresampled($out,$im,0,0,0,0,$w,$h,$irw,$irh);
header("Content-type: image/$type");
switch($ext) {				  // writes the image according to the extension
case 'jpeg':
case 'jpe':
case 'jpg':
imagejpeg($out,null,$q);
break;
case 'gif':
imagegif($out);
break;
case 'png':

imagepng($out);
break;
}
?>
