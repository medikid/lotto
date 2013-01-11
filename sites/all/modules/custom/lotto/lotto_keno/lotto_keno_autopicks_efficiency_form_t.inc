<?php
function get_lotto_keno_autopicks_efficiency_form_t(){
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
    
    $form['efficiency']['review_efficiency']=array(
	'#type'=>'button',
	'#value'=>t('Review'),
	'#ajax'=>array(
	    
	),
	'#suffix'=>'</div>'
    );
    
    
     $form['efficiency']['autopicks']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Autopicks:"),
	'#collapsible'=>true,
	'#collapsed'=>false
    );
     $form['efficiency']['autopicks']['validate_with_draw']=array(
	'#type'=>  'textfield',
	'#title'=>t("Validate With Draw#: "),
	'#default_value'=> $last_keno_draw_num + 1,
	'#size'=> 11,
	'#prefix'=>'<div class="container-inline">',
	'#suffix'=>'</div>'
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
    
     $form['efficiency']['diag_wins']['validate_with_draw']=array(
	'#type'=>  'textfield',
	'#title'=>t("Validate With Draw#: "),
	'#default_value'=> $last_keno_draw_num + 1,
	'#size'=> 11,
	'#prefix'=>'<div class="container-inline">',
	'#suffix'=>'&nbsp &nbsp'
    );
    
      
     $form['efficiency']['diag_wins']['number_of_draws'] = array(
	'#type'=>'textfield',
	'#title'=>t('Number Of Draws to Review: '),
	'#default_value'=>$num_of_draws_default,
	'#size'=>5,	 
	'#suffix'=>'</div>'
    );
     
     $form['efficiency']['diag_wins']['diag_wins_pattern'] = array(
	'#markup'=>lotto_patterns_diag_win_pattern_grid_create_t("lotto_keno", $last_keno_draw_num, $num_of_draws_default, $last_keno_draw_num + 1),
	'#prefix'=>'<div id="ajx_keno_diag_wins_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
     
    return $form;
}


function lotto_patterns_diag_win_pattern_grid_create_t($lottery_name, $draw_number, $num_of_results = 80, $draw_num_to_validate = null){
    
    if ( $draw_num_to_validate == null){
	$lotto_results = array();
    } else {
	$lotto_results = array();
	$draw_results = lotto_results_by_draw_number($lottery_name, $draw_num_to_validate);
	for($i=1; $i <= 20; $i++){
	    array_push($lotto_results, $draw_results['n'.$i]);
	}
    }
    
    
    $header = "<table class=\"diag_wins_pattern_grid\"><tbody>";
    
    $body = "<tr>";
    $body .= "<th>Rank</th>";
    $body .= "<th>Number(Step Up)</th><th>Ratio</th><th>Wins / Count</th>";
    $body .= "<th></th><th></th>";
    $body .= "<th>Number(Step Down)</th><th>Ratio</th><th>Wins / Count</th>";
    $body .= "</tr>";
    
    $diag_wins_ratio = lotto_patterns_diag_win_ratio($lottery_name, $draw_number, $num_of_results);
    $ratios_sorted = lotto_patterns_diag_win_ratio_sorted($diag_wins_ratio);
    
    foreach($ratios_sorted as $rank=>$data){
	$body .= "<tr>";
	$body .= "<th>".$rank."</th>";
	
	foreach($data['backward'] as $num_b=>$values_b){
	    $body .= ( in_array(($num_b+1), $lotto_results) ) ? "<td class=\"green\" >" : "<td>";
	    $body .= $num_b."</td>";
	    $body .= "<td>".$values_b['ratio']."</td>";
	    $body .= "<td>".$values_b['wins']." / ".$values_b['count']."</td>";
	}
	
	$body .= "<td></td><td></td>";
	
	foreach($data['forward'] as $num_f=>$values_f){
	    $body .= ( in_array(($num_f - 1), $lotto_results) ) ? "<td class=\"green\" >" : "<td>";
	    $body .= $num_f."</td>";
	    $body .= "<td>".$values_f['ratio']."</td>";
	    $body .= "<td>".$values_f['wins']." / ".$values_f['count']."</td>";
	}
	
	
	
	$body .= "</tr>";
    }
    
    
    
    $footer = "</tbody></table>";
    
    $diag_wins_pattern_grid = $header . $body . $footer;
    return $diag_wins_pattern_grid;    
}

?>