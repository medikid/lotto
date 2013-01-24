<?php

function get_lotto_keno_prize_table_form($form, $form_state){
    $form=array();
    $form['prize_table']['grid']=array(
	'#markup' => get_lotto_keno_prize_table_grid("lotto_keno")
    );
    
    return $form;
}
?>
