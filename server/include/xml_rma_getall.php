<?php
/**************************************************************************
    This file: ../web/helhed/include/xml_rma_getall.php is part of Helhed Client.

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
$knr = $_POST['knr'];
$k_id = "";
$sql = "select id from kunde where kundenr=$knr";
$res = mysql_query($sql,$link);
if(mysql_num_rows($res)>0) {
	$s = mysql_fetch_row($res);
	$k_id = $s[0];
	echo $head;
?>
<res>
<?php
	mysql_free_result($res);
	$sql = "select * from rma_info where k_id=$k_id";
	$rma = "select * from rma_data where rma_nr=";

	$res = mysql_query($sql,$link);
	if(mysql_num_rows($res)>0) {
		while($info = mysql_fetch_assoc($res)) {
			$title = "R768-" . str_pad($info["id"], 7, "0", STR_PAD_LEFT);
?>
 <rma>
  <id><?php echo $info["id"]; ?></id>
  <title><?php echo $title; ?></title>
  <onr><?php echo $info["onr"]; ?></onr>
  <email><?php echo unicode($info["email"]); ?></email>
  <dato><?php echo $info["dato"]; ?></dato>
  <vare>
   <vnr><?php echo unicode($info["v_nr"]); ?></vnr>
   <vtxt><?php echo unicode($info["v_txt"]); ?></vtxt>
   <vstk><?php echo $info["v_stk"]; ?></vstk>
   <vpris><?php echo number_format($info["v_pris"],2,',','.')?></vpris>
  </vare>
<?php
			if($info["e_dato"] != "") {
?>
  <replace>
   <edato><?php echo $info["e_dato"]; ?></edato>
   <enr><?php echo unicode($info["ev_nr"]); ?></vnr>
   <etxt><?php echo unicode($info["ev_txt"]); ?></vtxt>
   <estk><?php echo $info["ev_stk"]; ?></vstk>
   <epris><?php echo number_format($info["ev_pris"],2,',','.'); ?></vpris>
  </replace>
<?php
			}
			$dat = mysql_query($rma . $info["id"] . " order by dato,id",$link);
			if(mysql_num_rows($dat)>0) {
				$id=0;
				while($data = mysql_fetch_assoc($dat)) {
?>
  <data>
   <msg><?php echo unicode($data["msg"]); ?></msg>
   <ddato><?php echo $data["dato"]; ?></ddato>
   <type><?php echo $data["type"]; ?></type>
   <sid><?php echo $data["sid"]; ?></sid>
  </data>
<?php
				}
			}
?>
 </rma>
<?php
		}
	} else {
?>
<error><?php echo unicode("Der er ingen RMA sager p�\nden p�g�ldende kunde."); ?></error>
<?php
	}
?>
</res>
<?php
}
?>
