<?php
function draw_menu($id, $str, $main="", $class="")
{
  $click = "ajax_loadContent('main_body','". $main ."');";    
?>
      <tr id="<?php echo $id; ?>">
        <td class="menu_link <?php echo $class; ?>" onClick="<?php echo $click; ?>">
          <?php echo $str . "\n"; ?>
        </td>
      </tr>
<?php
}
?>
    <table border="0" cellpadding="0" cellspacing="0" height="100%">
<?php
  draw_menu("check","Status Page","greet.php","link");
  draw_menu("admin","Server Admin Access","install/admin_req.php");
  draw_menu("ftp","Ftp check","install/ftp_setup.php");
  draw_menu("unity","Unity DB","install/unity_db.php");
  draw_menu("crmadmin","Unity Admin Configured","install/unity_admin.php");
  draw_menu("install","Install Unity","install/install.php","link hidden");
?>
    </table>

