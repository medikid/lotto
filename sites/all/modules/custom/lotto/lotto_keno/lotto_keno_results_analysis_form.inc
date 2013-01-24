<?php

function get_lotto_keno_results_analysis_form($form, &$form_state){
    drupal_add_css(drupal_get_path('module', 'lotto_core') . '/css/number_grid.css', array('group' => CSS_DEFAULT, 'type' => 'file'));
    
    if (isset($draw_num)){
	$last_keno_draw_num = $draw_num;
    } else $last_keno_draw_num = get_last_keno_drawnumber("lotto_keno") - 1;
    $stat_type = 3;
    $lotto_stats = lotto_stats_by_draw_number("lotto_keno", $last_keno_draw_num, $stat_type);
    
    $form=array(
	'#prefix'=>'<div id="grid_form_wrapper">',
	'#suffix'=>'</div>'
	
    );
    $form['prev_btn']= array(
	'#type' => 'submit',
	'#value' => t('Prev'),
	'#prefix'=>'<div class="container-inline">',
	'#ajax' => array(
		'callback' => 'ajx_results_analysis_load_prev',
		'wrapper' => 'grid_form_wrapper',
		'method' => 'replace',
		'effect' => 'fade',
	      )
      );
    
    $form['lotto_draw_number'] = array(
	   '#type' => 'textfield',
	  '#title' => t('Draw#:'),
	  '#default_value' => $last_keno_draw_num,
	  '#size' => 12,
	  '#maxlength' => 12,
	   '#ajax' => array(
		'callback' => 'ajx_results_analysis_load',
		'wrapper' => 'grid_wrapper',
		'method' => 'replace',
		'effect' => 'fade',
	      )
	);
    $form['next_btn']= array(
	'#type' => 'submit',
	'#value' => t('Next'),
	'#suffix'=>'<div>',
	'#ajax' => array(
		'callback' => 'ajx_results_analysis_load_next',
		'wrapper' => 'grid_form_wrapper',
		'method' => 'replace',
		'effect' => 'fade',
	      )
      );  
    
    $form['grid']=array(
	'#type' => 'fieldset',
	'#title' => t('Results Analysis: '),
	'#collapsible' => TRUE,
	'#collapsed' => FALSE,
	'#prefix'=>'<div id="grid_wrapper" >',
	'#suffix'=>'</div>'
    );
    

    
    $form['grid']['result_grid'] = array(
	'#markup' => lotto_result_grid_analysis('lotto_keno', $lotto_stats['lksid'])
    );
    
    $form['grid']['skipped_grid'] = array(
	'#markup' => lotto_skipped_grid_analysis('lotto_keno',$lotto_stats['lksid'])
    );
    
    return $form;
}

function ajx_results_analysis_load($form, $form_state){
    $lotto_draw_number = $form_state['values']['lotto_draw_number'];
    $stat_type = 3;
    $lotto_stats = lotto_stats_by_draw_number("lotto_keno", $lotto_draw_number, $stat_type);
    $lotto_stat_id = $lotto_stats['lksid'];
    
    $form['grid']['#collapsed'] = FALSE ;
    $form['grid']['#prefix']='<div id="grid_wrapper" >';
    $form['grid']['#suffix']='</div>';
    
    $form['grid']['result_grid']['#markup'] = lotto_result_grid_analysis('lotto_keno', $lotto_stat_id);
    $form['grid']['skipped_grid']['#markup'] = lotto_skipped_grid_analysis('lotto_keno', $lotto_stat_id);
    
    return $form['grid'];
}

function ajx_results_analysis_load_next($form, $form_state){
    $lotto_draw_number = $form_state['input']['lotto_draw_number'];
    $lotto_draw_number_next = $lotto_draw_number + 1;
    $form['lotto_draw_number']['#value'] = $lotto_draw_number_next;
    
    $stat_type = 3;
    $lotto_stats = lotto_stats_by_draw_number("lotto_keno", $lotto_draw_number_next, $stat_type);
    $lotto_stat_id_next = $lotto_stats['lksid'];
    
    $form['grid']['#collapsed'] = FALSE ;
    $form['grid']['#prefix']='<div id="grid_wrapper" >';
    $form['grid']['#suffix']='</div>';
    
    $form['grid']['result_grid']['#markup'] = lotto_result_grid_analysis('lotto_keno', $lotto_stat_id_next);
    $form['grid']['skipped_grid']['#markup'] = lotto_skipped_grid_analysis('lotto_keno', $lotto_stat_id_next);
    
    return $form;
}
function ajx_results_analysis_load_prev($form, $form_state){
    $lotto_draw_number = $form_state['input']['lotto_draw_number'];
    $lotto_draw_number_prev = $lotto_draw_number - 1;
    $form['lotto_draw_number']['#value'] = $lotto_draw_number_prev;
    
    $stat_type = 3;
    $lotto_stats = lotto_stats_by_draw_number("lotto_keno", $lotto_draw_number_prev, $stat_type);
    $lotto_stat_id_prev = $lotto_stats['lksid'];
    
    $form['grid']['#collapsed'] = FALSE ;
    $form['grid']['#prefix']='<div id="grid_wrapper" >';
    $form['grid']['#suffix']='</div>';
    
    $form['grid']['result_grid']['#markup'] = lotto_result_grid_analysis('lotto_keno', $lotto_stat_id_prev);
    $form['grid']['skipped_grid']['#markup'] = lotto_skipped_grid_analysis('lotto_keno', $lotto_stat_id_prev);
    
    return $form;
}
?>
