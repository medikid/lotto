<?php

function get_lotto_keno_autopicks_efficiency_report_form($form, $form_state){
    
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno");
    $num_of_draws_default = 15;
    
    $form['efficiency']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['draw_number']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw#: "),
	'#default_value'=> $last_keno_draw_num,
	'#size'=> 11	
    );
    
    $form['efficiency']['num_of_draws']=array(
	'#type'=>  'textfield',
	'#title'=>t("Number of Draws: "),
	'#default_value'=> $last_keno_draw_num,
	'#size'=> 11	
    );
    $form['efficiency']['review_efficiency']=array(
	'#type'=>'button',
	'#value'=>t('Review'),
	'#ajax'=>array(
	    
	),
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['efficiency_report']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Result Patterns:"),
	'#collapsible'=>true,
	'#collapsed'=>true
    );
    
    $form['efficiency']['efficiency_report']['report'] = array(
	'#markup'=>get_lotto_patterns_autopicks_efficiency_report_create("lotto_keno", $last_keno_draw_num, $num_of_draws_default, $last_keno_draw_num + 1),
	'#prefix'=>'<div id="ajx_keno_diag_wins_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    return $form;
}

function lotto_patterns_autopicks_efficiency_report_create($lottery_name, $draw_num, $num_of_draws=50, $draw_num_val=null){
       
    
    
}

function lotto_patterns_autopicks_efficiency_report_config($lottery_name, $draw_num, $num_of_draws=50, $draw_num_val=null){
       
    $autopicks_effic
    
}


?>
