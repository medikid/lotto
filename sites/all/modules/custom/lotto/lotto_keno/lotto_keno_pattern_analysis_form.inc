<?php

Function get_lotto_keno_pattern_analysis_form($form, &$form_state){
    $form = array();
    
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    drupal_add_js(drupal_get_path('module', 'lotto_core') . '/js/pattern_grid.js' );
    
    $form=array(   );
    
    $form['pattern_refresh']=array(
	'#type'=>'button',
	'#value'=>'Refresh Results',
	'#ajax'=>array(
	    'callback' => 'ajx_keno_results_pattern_refresh',
	    'wrapper'=>'ajx_keno_results_pattern_wrapper',
	    'method'=>'replace'
	),
	'#prefix'=>'<div class="container-inline">',
    );
    
   
    $form['bets']['pattern_grid'] = array(
	'#markup'=> lotto_pattern_grid_create("lotto_keno"),
	'#prefix'=>'<div id="ajx_keno_results_pattern_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    
    return $form;
}
?>
