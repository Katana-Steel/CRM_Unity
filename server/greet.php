<?php
session_start();
$out = array();
function getTz($str) {
    $ret = $str;
    $tz = array("PST8PDT","EST5EDT", "CST6CDT", "MST7MDT");
    foreach($tz as $t)
        if(stripos($t,$str) !== FALSE) {
            $ret = $t;
            break;
        }
    return $ret;
}
if(isset($_SESSION['timezone'])) {
    date_default_timezone_set($_SESSION['timezone']);
} else {
    date_default_timezone_set("CET");
    $_SESSION['timezone'] = getTz(timezone_name_get(date_timezone_get(date_create($_GET['tz']))));
}
$out[] = "timezone: " . $_SESSION['timezone'];


if(file_exists("include/startdb.php")) {
    $out[] = "The database has already been configured";
    $out[] = "looks Like you have a working server";
}
// do the session have admin access to the database
$dbadmin = 0;
if(isset($_SESSION['dbhost'])) {
    $link = mysql_connect($_SESSION['dbhost'],$_SESSION['dbuser'],$_SESSION['dbpass']);
    $res = mysql_query("show grants",$link);
    while($r = mysql_fetch_row($res)) {
        $p = stripos($r[0], "grant");
        if($p !== false) {
            $dbadmin = 1;
            break;
        }
    }
    mysql_free_result($res);
}
$_SESSION['dbadmin'] = $dbadmin;

$ftpsetup = 0;
// a simple ftp login check:
if(file_exists("app/config.xml")) {
    $out[] = "found <a href='app/config.xml'>config.xml</a>";
    $out[] = "you might have a working installation.";
    $cfgfile = explode("\n",file_get_contents("app/config.xml"));
/*    $host = $cfgfile[4];
    $s = strpos($host,">")+1;
    $e = strpos($host,"<",$s);
    $host = substr($host,$s,($e-$s));
    $port = $cfgfile[5];
    $s = strpos($port,">")+1;
    $e = strpos($port,"<",$s);
    $port = substr($port,$s,($e-$s)); */
    $user = $cfgfile[8];
    $s = strpos($user,">")+1;
    $e = strpos($user,"<",$s);
    $user = substr($user,$s,($e-$s));
    $pass = $cfgfile[9];
    $s = strpos($pass,">")+1;
    $e = strpos($pass,"<",$s);
    $pass = substr($pass,$s,($e-$s));
    
/*    $ftp = ftp_connect($host,$port);
    $log = false;
    if($ftp !== FALSE) {
        $log = ftp_login($ftp, $user, $pass);
        ftp_close($ftp);
    }
    if($log) 
        $ftpsetup = 2;
*/
}

if(!$ftpsetup && isset($_SESSION['v_ftp_db']) && $dbadmin) {
    mysql_select_db($_SESSION['v_ftp_db'], $link);

    $fuser = $_SESSION['v_ftp_user'];
    $res = mysql_query("select * from ${_SESSION['v_ftp_login_table']}",$link);
    while(($r = mysql_fetch_assoc($res)) && !$ftpsetup)
    {
        foreach($r as $v)
            if($v == $fuser) $ftpsetup = 1;
        
        if($ftpsetup)
            $_SESSION['v_ftp_homedir'] = $r['homedir'];
        
    }
    mysql_free_result($res);
}
$_SESSION['ftpsetup'] = $ftpsetup;
$_SESSION['unity'] = 0;
if(isset($_SESSION['unity_db_name']) && $dbadmin) {
    $_SESSION['unity'] = 1;
    if(mysql_select_db($_SESSION['unity_db_name']))
        $out[] = "looks like it the Database has been created";
}
$_SESSION['crmadmin'] = 0;
if(isset($_SESSION['crm_admin_mail'])) {
    $_SESSION['crmadmin'] = 1;
}
$_SESSION['unity_app_path'] = str_replace("greet","app", $_SERVER['SCRIPT_NAME']);

if(isset($link)) 
  mysql_close($link);
?>
<p align='center'>
&lt;-- Systems Check --&gt;<br />
<?php
 echo "server: " . $_SERVER['SERVER_NAME'] . "<br />\n";
 echo "http://" . $_SERVER['SERVER_NAME'] . $_SESSION['unity_app_path'] . ": " . ((file_exists($_SERVER['DOCUMENT_ROOT'] . $_SESSION['unity_app_path'])) ? "Ok" : "!Not Found!") . "<br />\n";
 echo "Make sure the above is what you want, else try to load the install from another location.<br />\n";
 foreach($out as $l)
    echo $l . "<br />\n";
?>
</p>
<script type="text/javascript">
function check() {
  var showInstall = 1;
  var a = document.getElementById('admin');
  var t = <?php echo $_SESSION['dbadmin']; ?>;
  if(t) {
    a.style.backgroundColor = 'lime';
  } else {
    showInstall = 0;
    a.style.backgroundColor = 'red';    
  }
  a = document.getElementById('ftp');
  t = <?php echo $_SESSION['ftpsetup']; ?>;
  if(t) {
    a.style.backgroundColor = 'lime';
  } else {
    showInstall = 0;
    a.style.backgroundColor = 'red';
  }
  if(t > 1) {
    a.cells[0].innerHTML += '\n<br />found app/config.xml';
  }
  a = document.getElementById('unity');
  t = <?php echo $_SESSION['unity']; ?>;
  if(t) {
    a.style.backgroundColor = 'lime';
  } else {
    showInstall = 0;
    a.style.backgroundColor = 'red';
  }
  a = document.getElementById('crmadmin');
  t = <?php echo $_SESSION['crmadmin']; ?>;
  if(t) {
    a.style.backgroundColor = 'lime';
  } else {
    showInstall = 0;
    a.style.backgroundColor = 'red';
  }
  if(showInstall) {
    a = document.getElementById('install');
    for(i=0;i<a.cells.length;i++)
        a.cells[i].style.display = "table-cell";
  }
}
window.setTimeout('check();',1500);
</script>
<p align='center'>
&lt;-- Sql Check --&gt;
</p>
