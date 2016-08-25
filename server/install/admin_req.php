<form id="dbaccess">
<table height="100%">
<tr>
 <td colspan="2"><div id="reload"></div></td>
</tr>
<tr>
<td>host:</td><td><input type="text" name="host" /></td>
</tr>
<tr>
<td>user:</td><td><input type="text" name="user" /></td>
</tr>
<tr>
<td>pass:</td><td><input type="text" name="pass" /></td>
</tr>
<td colspan="2" align="center"><input type="button" value="Set Admin" onClick="submit_form('reload','dbaccess');" /></td>
</tr>
</table>
<input type="hidden" id="tz" name="dtime" />
</form>
<script type="text/javascript">
    var tz = new Date();
    var a = document.getElementById("tz");
    a.value = tz.toLocaleString();
  add_form('dbaccess','install/set_admin.php','POST');
</script>