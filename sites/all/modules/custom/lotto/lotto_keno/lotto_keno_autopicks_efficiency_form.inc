<?php

function get_lotto_keno_autopicks_efficiency_form(){
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    $form = array();
    $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno");
    $num_of_draws_default = 50;
    
    $form['efficiency']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks Efficiency:"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['draw_number_prev']=array(
	'#type'=>'button',
	'#value'=>t('Prev'),
	'#ajax'=>array(
	    'callback' => 'ajx_draw_number_prev',
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
	    'callback' => 'ajx_draw_number_next',
	    'wrapper'=>'ajx_autopicks_efficiency_wrapper',
	    'method'=>'replace'
	),
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
    
    $form['efficiency']['show_result_patterns']=array(
	'#type'=>'checkbox',
	'#title'=>t("Show Results: "),
	'#default_value'=>0,
	'#ajax'=>array(
	    'callback' => 'ajx_show_result_patterns',
	    'wrapper'=>'ajx_result_patterns_wrapper',
	    'method'=>'replace'
	),
	'#suffix'=>'</div>'
	);
    
    $form['efficiency']['results']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Result Patterns:"),
	'#collapsible'=>true,
	'#collapsed'=>true,	
	'#prefix'=>'<div id="ajx_result_patterns_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['results']['validate_with_draw']=array(
	'#type'=>  'textfield',
	'#title'=>t("Validate With Draw#: "),
	'#default_value'=> $last_keno_draw_num + 1,
	'#size'=> 11,
	'#prefix'=>'<div class="container-inline">',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['results']['results_grid'] = array(
	'#markup'=> lotto_patterns_grid_by_drawnum_create("lotto_keno", $last_keno_draw_num, $num_of_draws_default, $last_keno_draw_num + 1 ),
	'#prefix'=>'<div id="ajx_keno_results_wrapper" >',
	'#suffix'=>'</div>'
    );
    
     $form['efficiency']['autopicks']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks:"),
	'#collapsible'=>true,
	'#collapsed'=>false
    );
     
     $form['efficiency']['autopicks']['numbers']=array(
	'#markup'=> lotto_patterns_autopicks_grid_create("lotto_keno", $last_keno_draw_num, $last_keno_draw_num + 1)
    );
    
     $form['efficiency']['diag_wins']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Diagwins:"),
	'#collapsible'=>true,
	'#collapsed'=>false
    );
 
     $form['efficiency']['diag_wins']['number_of_draws'] = array(
	'#type'=>'textfield',
	'#title'=>t('Number Of Draws to Review: '),
	'#default_value'=>$num_of_draws_default,
	'#size'=>5,
	'#prefix'=>'<div class="container-inline">',
	'#suffix'=>'</div>'
    );
     
     $form['efficiency']['diag_wins']['diag_wins_pattern'] = array(
	'#markup'=>lotto_patterns_diag_win_pattern_grid_create("lotto_keno", $last_keno_draw_num, $num_of_draws_default, $last_keno_draw_num + 1),
	'#prefix'=>'<div id="ajx_keno_diag_wins_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
     
    return $form;
}

function ajx_draw_number_prev($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_number = $form_state['values']['draw_number'];
    $num_of_draws = $form_state['values']['number_of_draws'];
    $show_result_patterns = $form_state['values']['show_result_patterns'];
    
    $draw_number_prev = $draw_number - 1;
    $form['efficiency']['draw_number']['#value'] = $draw_number_prev;
    
    $draw_number_val = $draw_number_prev + 1;
    
    $form['efficiency']['results']['validate_with_draw']['#value'] = $draw_number_val;
    if ($show_result_patterns == 1){
	$form['efficiency']['results']['results_grid']['#markup'] = get_lotto_patterns_result_grid($form, $form_state);
    }
    $form['efficiency']['autopicks']['numbers']['#markup'] = lotto_patterns_autopicks_grid_create($lottery_name, $draw_number_prev, $draw_number_val);
    $form['efficiency']['diag_wins']['diag_wins_pattern']['#markup'] = lotto_patterns_diag_win_pattern_grid_create($lottery_name, $draw_number_prev, $num_of_draws, $draw_number_val);
    
    return $form['efficiency'];
}

function ajx_draw_number_next($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_number = $form_state['values']['draw_number'];
    $num_of_draws = $form_state['values']['number_of_draws'];
    $show_result_patterns = $form_state['values']['show_result_patterns'];
    
    $draw_number_next = $draw_number + 1;
    $form['efficiency']['draw_number']['#value'] = $draw_number_next;
    
    $draw_number_val = $draw_number_next + 1;
    
    $form['efficiency']['results']['validate_with_draw']['#value']  = $draw_number_val;
    if ($show_result_patterns == 1){
	$form['efficiency']['results']['results_grid']['#markup'] =get_lotto_patterns_result_grid($form, $form_state);
    }
    $form['efficiency']['autopicks']['numbers']['#markup'] = lotto_patterns_autopicks_grid_create("lotto_keno", $draw_number_next, $draw_number_val);
    $form['efficiency']['diag_wins']['diag_wins_pattern']['#markup'] = lotto_patterns_diag_win_pattern_grid_create($lottery_name, $draw_number_next, $num_of_draws, $draw_number_val);
    
    return $form['efficiency'];
}

function ajx_autopicks_efficiency_refresh($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_number = $form_state['values']['draw_number'];
    $num_of_draws = $form_state['values']['number_of_draws'];
    $show_result_patterns = $form_state['values']['show_result_patterns'];
    $draw_number_val = $form_state['values']['validate_with_draw'];
    
    if ($show_result_patterns == 1){
	$form['efficiency']['results']['results_grid']['#markup'] = get_lotto_patterns_result_grid($form, $form_state);
    }
    $form['efficiency']['autopicks']['numbers']['#markup'] = lotto_patterns_autopicks_grid_create("lotto_keno", $draw_number, $draw_number_val);
    $form['efficiency']['diag_wins']['diag_wins_pattern']['#markup'] = lotto_patterns_diag_win_pattern_grid_create($lottery_name, $draw_number, $num_of_draws, $draw_number_val);
    
    return $form['efficiency'];
}


function get_last_keno_drawnumber($lottery_name){
    $last_results = lotto_results_last_available($lottery_name); 
    return $last_results['draw_number'];
    
}

function get_lotto_patterns_result_grid($form, $form_state){
    $lottery_name = "lotto_keno";
    $draw_num = $form_state['values']['draw_number'];
    $num_of_draws = $form_state['values']['number_of_draws'];
    $draw_num_val = $form_state['values']['validate_with_draw'];
    
    $results_pattern_grid = lotto_patterns_grid_by_drawnum_create($lottery_name, $draw_num, $num_of_draws, $draw_num_val );

    return $results_pattern_grid;
}

function ajx_show_result_patterns($form, $form_state){
    $show_result_patterns = $form_state['values']['show_result_patterns'];
    $result_patterns_grid = "";
    if ($show_result_patterns == 1){
	$result_patterns_grid = get_lotto_patterns_result_grid($form, $form_state);
    }
    $form['efficiency']['results']['results_grid']['#collapsed'] = false;
    $form['efficiency']['results']['results_grid']['#markup'] = $result_patterns_grid;
    
    return $form['efficiency']['results'];
}

?>
