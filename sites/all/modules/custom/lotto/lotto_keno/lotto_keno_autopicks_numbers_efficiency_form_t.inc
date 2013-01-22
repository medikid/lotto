<?php

function get_lotto_keno_autopicks_numbers_efficiency_form_t($form, &$form_state){
    
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    if (isset($draw_num)){
	$last_keno_draw_num = $draw_num;
    } else $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno") - 1;
    $last_keno_draw_num_val = $last_keno_draw_num + 1;
    $top_of = 10;
    
    $numbers_spiral = get_lotto_autopicks_apd_numbers_quick("lotto_keno", $last_keno_draw_num, $last_keno_draw_num_val);
       
    $form['efficiency']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks Numbers Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['draw_number_prev']=array(
	'#type'=>'button',
	'#value'=>t('Prev'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_prev_t',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
	'#prefix'=>'<div class="container-inline">',
    );	

    
    $form['efficiency']['draw_number']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw#: "),
	'#default_value'=> $last_keno_draw_num,
	'#size'=> 11	
    );
    
    $form['efficiency']['draw_number_next']=array(
	'#type'=>'button',
	'#value'=>t('Next'),
	'#ajax'=>array(
	    'callback' => 'ajx_numbers_draw_number_next_t',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    );
    $form['efficiency']['autopicks_profile'] = array(
	'#type'=>'select',
	'#title'=>'Profile:',
	'#options'=>array(
	    0=>'Select Profile',
	    1=>'DiagWinNormal',
	    2=>'DiagWinNormal-t',
	    3=>'DiagWinSpiral',
	    4=>'DiagWinSpiral-t'
	),
	'#default_value'=>4
    );
    
    
    $form['efficiency']['refresh']=array(
	'#type'=>'button',
	'#value'=>t('Refresh'),
	'#ajax'=>array(
	    'callback' => 'ajx_autopicks_efficiency_refresh',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
    );
     
    $form['efficiency']['top_of']=array(
	'#type'=>  'textfield',
	'#title'=>t("No of Picks#: "),
	'#default_value'=>15,
	'#size'=> 11	
    );
    
    $form['efficiency']['draw_number_val']=array(
	'#type'=>  'textfield',
	'#title'=>t("Draw Result#: "),
	'#default_value'=>$last_keno_draw_num_val,
	'#size'=> 11	
    );
    
    
    $form['efficiency']['numbers']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['numbers']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral("lotto_keno", $numbers_spiral)
	
    );
    
     $form['efficiency']['numbers_pattern']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Pattern:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['numbers_pattern']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral("lotto_keno", $numbers_spiral),
	
    );
    
    $form['efficiency']['numbers_score']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Numbers Score:"),
	'#collapsible'=>true,
	'#collapsed'=>false,	
	'#prefix'=>'<div id="ajx_autopicks_efficiency_numbers_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    $form['efficiency']['numbers_score']['grid']=array(
	'#markup'=>lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral)	
    );
    return $form;
}

function ajx_numbers_draw_number_prev_t($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $form_state['values']['draw_number_val'];
    $draw_num_prev = $draw_num-1;
    $draw_num_prev_val = $draw_num_val - 1;
    $top_of = $form_state['values']['top_of'];
    
    $numbers_spiral = get_lotto_autopicks_apd_numbers_quick("lotto_keno", $draw_num_prev, $draw_num_prev_val );
    $numbers_grid = lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_pattern_grid = lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_score_grid = lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_prev;
    $form['efficiency']['draw_number_val']['#value'] = $draw_num_prev_val;
    $form['efficiency']['numbers']['grid']['#markup'] = $numbers_grid;
    $form['efficiency']['numbers_pattern']['grid']['#markup'] = $numbers_pattern_grid;
    $form['efficiency']['numbers_score']['grid']['#markup'] = $numbers_score_grid;
    
	
    return $form['efficiency'];
}

function ajx_numbers_draw_number_next_t($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $form_state['values']['draw_number_val'];
    $draw_num_next = $draw_num + 1;
    $draw_num_next_val = $draw_num_val + 1;
    $top_of = $form_state['values']['top_of'];
    
    $numbers_spiral = get_lotto_autopicks_apd_numbers_quick("lotto_keno", $draw_num_next, $draw_num_next_val);
    $numbers_grid = lotto_keno_autopicks_pillar_diagwin_numbers_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_pattern_grid = lotto_keno_autopicks_pillar_diagwin_numbers_pattern_grid_create_spiral("lotto_keno", $numbers_spiral);
    $numbers_score_grid = lotto_keno_autopicks_pillar_diagwin_numbers_score_grid_create_spiral("lotto_keno", $numbers_spiral);
    
    $form['efficiency']['draw_number']['#value'] = $draw_num_next;
    $form['efficiency']['draw_number_val']['#value'] = $draw_num_next_val;
    $form['efficiency']['numbers']['grid']['#markup'] = $numbers_grid;
    $form['efficiency']['numbers_pattern']['grid']['#markup']= $numbers_pattern_grid;
    $form['efficiency']['numbers_score']['grid']['#markup'] = $numbers_score_grid; 
    
    return $form['efficiency'];
}


?>
