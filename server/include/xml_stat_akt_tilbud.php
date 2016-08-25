<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_stat_akt_tilbud.php is part of Helhed Client.

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
?>
<?php
  $pro = $_POST['pro'];
  $sql = "select k_id,tilbud_nr from K_notat where tilbud_type='T' and status='A' and saelger_id='$usr' and ";
  if(isset($_POST['G'])) $sign = ">";
  if(isset($_POST['L'])) $sign = "<";
  $sql .= "( ";
  if($pro != 100) {
    $sql .= "lukke_pro $sign $pro";
	if($sign == ">") $sql .= " or lukke_pro=1";
	else $sql .= " and lukke_pro!=1";
  } else {
    if($sign == "<") $sql .= "lukke_pro $sign $pro";
    else $sql .= "lukke_pro=1";
  }
  $sql .= " ) order by k_id,tilbud_nr desc";
  echo $head;
?>
<res>
<debug><?php echo
 unicode("Statestik funktionen du valgte,\nbrugte denne sql streng.\n\n".
 		 str_replace("<","&lt;",str_replace(">","&gt;",$sql)));
?></debug><?php
  $res = mysql_query($sql,$link);
  $rows = mysql_num_rows($res);
  $kid = 0;
  while($r = mysql_fetch_row($res)) {
  if($kid != $r[0]) {
    if($kid != 0) echo " </tlist>";
	$kid = $r[0];
	$kdat = GetFK_OP($kid,$link);
?>
 <tlist>
  <kid><?php echo $kid; ?></kid>
  <knr><?php echo $kdat["knr"]; ?></knr>
  <firma><?php echo unicode($kdat["firma"]); ?></firma>
  <name><?php echo unicode($kdat["navn"]); ?></name>
<?php } ?>
  <tnr><?php echo $r[1]; ?></tnr>
<?php }
if($rows > 0) echo " </tlist>\n";
mysql_close($link);
?>
</res>
