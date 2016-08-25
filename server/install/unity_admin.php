<?php 
srand(time(0));
$auser = "adm";
$apass = "";
for($i=0;$i < 4;$i++)
    $auser .= rand(0,9);
for($i=0;$i < 4;$i++)
    $apass .= rand(0,9);
?>
<action id="dbaccess">
<table height="100%">
<tr>
 <td colspan="2"><div id="reload"></div></td>
</tr>
<tr>
<td>Admin username:</td><td><input type="text" name="auser" value="<?= $auser ?>"/></td>
</tr>
<tr>
<td>Admin password:</td><td><input type="text" name="apass" value="<?= $apass ?>"/></td>
</tr>
<tr>
<td>Admin Email:</td><td><input type="text" name="amail"/></td>
</tr>
<tr>
<td colspan="2" align="center"><input type="button" value="Set Admin" onClick="submit_form('reload','dbaccess');" /></td>
</tr>
</table>
</action>
<script type="text/javascript">
  add_form('dbaccess','install/set_unity_admin.php','POST');
</script>
