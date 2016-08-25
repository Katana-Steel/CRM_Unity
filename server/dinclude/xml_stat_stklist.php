<?
/**************************************************************************
    This file: /var/www/html/helhed/dinclude/xml_stat_stklist.php is part of Helhed Server.

    Helhed Server is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Helhed Client is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Helhed Client.  If not, see <http://www.gnu.org/licenses/>.

    Copyright 2008, 2009 RenÃ© Kjellerup aka Katana Steel
**************************************************************************/
?>
<?
 $t = isset($_POST['T']);
 $o = isset($_POST['O']);
 $k = isset($_POST['K']);
 $to = $_POST['to'];
 $from = $_POST['from'];
 $tt = mktime(1,0,0,substr($to,5,2),substr($to,8,2),substr($to,0,4));
 $tdat = strftime("den %e. %B, %Y",$tt);
 $ft = mktime(1,0,0,substr($from,5,2),substr($from,8,2),substr($from,0,4));
 $fdat = strftime("den %e. %B, %Y",$ft);
 
 $str = str_replace("'","",str_replace("\\","",funicode($_POST['str'])));
 $type = "";
 if($t)          $type .= "type = 'T'";
 if($type != "" && ($o || $k)) $type .= " or ";
 if($o)          $type .= "type = 'O'"; 
 if($type != "" && $k && $o) $type .= " or "; 
 if($k)          $type .= "type = 'K'";
 
 $ktil  = "select * from `K-tilbud` where ( $type ) and ( ";
 $ktil .= "vare_nr like '%$str%' or varetekst like '%$str%'";
 $ktil .= " ) and ( dato <= '$to' and dato >= '$from' ) ";
 
 $res = mysql_query($ktil,$link);
 echo $head;
 if(mysql_num_rows($res) == 0) {
?>
<res>
  <error><?= unicode("Der blev ikke fundet nogen stk\nder matcher dine søge kriterier") ?></error>
</res>
<? } else { 
 $ary = array();
 while($r = mysql_fetch_assoc($res)) { 
   if($r["stk"] > 0 ) {
     $ary[$r["vare_nr"]][$r["varetekst"]] += $r["stk"];
   }
 } 
?>
<res>
 <flags><?
 if($t) echo "T";
 if($o) echo "O";
 if($k) echo "K";
 ?></flags>
 <str><?= unicode($str) ?></str>
 <fdat><?= unicode($fdat) ?></fdat>
 <tdat><?= unicode($tdat) ?></tdat>
<?
  foreach ( $ary as $vnr => $lst ) {
   foreach ( $lst as $vtxt => $stk ) {
?>
 <item>
  <stk><?= unicode($stk) ?></stk>
  <vnr><?= unicode($vnr) ?></vnr>
  <vtxt><?= unicode($vtxt) ?></vtxt>
 </item>
<?
   }
  }
?>
</res>
<? } ?>
