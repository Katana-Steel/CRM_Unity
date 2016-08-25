<?php
/**************************************************************************
    This file: ../web/helhed/index.php is part of Helhed Client.

    Helhed Client is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009 René Kjellerup aka Katana Steel
**************************************************************************/

$rpath = $_SERVER['SCRIPT_NAME'];
$lpos = strrpos($rpath, '/');
$rpath = substr($rpath, 0,$lpos);
/**************************************************************************
 * extensions: page top & page bottom copied from include.php
 **************************************************************************/
function page_bottom() {
$ret="";
include('include/page_bottom.php');
return $ret;
}

function page_top($str,$id) {
$ret = "";
include('include/page_top.php');
return $ret;
}

$index = true;

function setup()
{
 $ret = false;
 if(file_exists('setup.php')) {
  include('setup.php');
 }
 return $ret;
}

function install($dbuser,$dbpass,$dbname,$dbhost,$ftp_path,$admin_user="",$admin_pass="")
{
 $ret = false;
 if(file_exists('install.php')) {
  include('install.php');
 }
 if($ret) {
  rename('install.php', 'app/install.bck');
  rename('setup.php',   'app/setup.bck');
  // delete setup and install files here
 }
 return $ret;
}

if(isset($_POST["dbname"])) {
// install returns true it have diplayed a page and index shouldn't be posted
  if(install($_POST["dbuser"], $_POST["dbpass"], $_POST["dbname"], $_POST["dbhost"],
             $_POST['ftphome'],$_POST["aduser"], $_POST["adpass"])) {
    $index = false;
  } else {
    // if install fails display the setup page again.
    if(setup()) $index = false;
  }
} else {
// if setup returns true it have diplayed a page and index shouldn't be posted
  if(setup()) $index = false;
}

if($index) {
?>
<html>
<head>
<title>Running system - Helhed</title>
</head>
<body style="margin: 0px;">
<?php echo page_top("Helhed",""); ?>
the Client Configuration <a href="app/config.xml">config.xml</a><br />
<?php
  if(file_exists("app/dev_config.xml")) {
?><br />
the Client Configuration <a href="app/dev_config.xml">dev_config.xml</a> for the Development server.<br />
To use it remember to rename it to config.xml or to what ever your client need it to be.<br />
<?php
  }
  if(isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] != "off") {
    /* parse the apache configuration of the SSL enabled VHost to find the certificate */
    if(!file_exists("server.cert"))
        copy("/etc/ssl/certs/ssl-cert-snakeoil.pem","server.cert");
  }
  if(file_exists("server.cert")) {

?><br />
SSL has been detected as in use. So either export the active certificate and save it to the plugins<br />
directory of the client as "server.cert", or download this file <a href="server.cert">server.cert</a> to the same.<br />
<?php
  }
  echo page_bottom();
}
?>
