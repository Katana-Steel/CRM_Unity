<?php 
session_start();
$home = "";
if(isset($_SESSION['v_ftp_homedir']))
    $home = $_SESSION['v_ftp_homedir'];
?>
<action id="dbaccess">
<table height="100%">
<tr>
 <td colspan="2"><div id="reload"></div></td>
</tr>
<tr>
<td>set upload dir:</td><td><input type="text" name="updir" value="<?= $home ?>"/></td>
</tr>
<tr>
<td>Unity database name:</td><td><input type="text" name="dbname" value="unity"/></td>
</tr>
<tr>
<td>Customer table name:</td><td><input type="text" name="ctable" value="customer"/></td>
</tr>
<tr>
<td>db user:</td><td><input type="text" name="user" /></td>
</tr>
<tr>
<td>db pass:</td><td><input type="text" name="pass" /></td>
</tr>
<td colspan="2" align="center"><input type="button" value="Set Admin" onClick="submit_form('reload','dbaccess');" /></td>
</tr>
</table>
</action>
<script type="text/javascript">
  add_form('dbaccess','install/set_unity_db.php','POST');
</script>
