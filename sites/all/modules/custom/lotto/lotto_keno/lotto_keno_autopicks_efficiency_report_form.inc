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
	'#size'=> 11,
	'#prefix'=>'<div class="container-inline" >'
    );
    
    $form['efficiency']['num_of_draws']=array(
	'#type'=>  'textfield',
	'#title'=>t("Number of Draws: "),
	'#default_value'=> $num_of_draws_default,
	'#size'=> 11	
    );
    $form['efficiency']['review_efficiency']=array(
	'#type'=>'button',
	'#value'=>t('Refresh'),
	'#ajax'=>array(
	    'callback' => 'ajx_autopicks_efficiency_report',
	    'wrapper'=>'ajx_autopicks_efficiency_report_wrapper',
	    'method'=>'replace'
	),
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['efficiency_report']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Efficiency Report(t-validateDiagwin):"),
	'#collapsible'=>true,
	'#collapsed'=>false,
	'#prefix'=>'<div id="ajx_autopicks_efficiency_report_wrapper" >',
	'#suffix'=>'</div>'
    );
    
    $form['efficiency']['efficiency_report']['report']  = array(
	'#markup'=>'',//get_lotto_patterns_autopicks_efficiency_report("lotto_keno", 1563918, 1563919, 10),
	
    );
    
      $form['efficiency']['efficiency_report']['report_spiral']=array(
	'#type'=>  'fieldset',
	'#title'=>t("Efficiency Report(spiral-win):"),
	'#collapsible'=>true,
	'#collapsed'=>false
    );
    
    $form['efficiency']['efficiency_report']['report_spiral']['report'] = array(
	'#markup'=>'',//get_lotto_patterns_autopicks_efficiency_report("lotto_keno", 1563918, 1563919, 10),	
    );
    return $form;
}



function lotto_patterns_autopicks_efficiency_report_create($lottery_name, $draw_num, $num_of_draws=50, $draw_num_val=null){
       
    
    
}

function lotto_patterns_autopicks_efficiency_report_data($lottery_name, $draw_num, $draw_num_val){
    $report_numbers = get_autopicks_efficiency_report_numbers($lottery_name, $draw_num, $draw_num_val);
    $report_data = array();
    $report_data['draw_details'] = $report_numbers['draw_details'];
    
    $lotto_results = $report_numbers['lotto_results'];
    /*********************AUTOPICKs***********************************/
    $autopicks = $report_numbers['autopick_nbrs'];    
    
    $report_data['autopicks']['diagonal']['match'] = 0;
    $report_data['autopicks']['diagonal']['count'] = count($autopicks['diagonal']);    
    foreach( $autopicks['diagonal'] as $num_d){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['diagonal']['match']++;
	}
    }
    
    $report_data['autopicks']['ladder']['match'] = 0;
    $report_data['autopicks']['ladder']['count'] = count($autopicks['ladder']);    
    foreach( $autopicks['ladder'] as $num_l){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['ladder']['match']++;
	}
    }
    /*********************DIAGWIN-5***********************************/
    $diagwin5 = $report_numbers['diagwin5'];
    
    $report_data['diagwin5']['stepup']['match'] = 0;
    $report_data['diagwin5']['stepup']['count'] = count($diagwin5['stepup']);    
    foreach( $diagwin5['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin5']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin5']['stepdown']['match'] = 0;
    $report_data['diagwin5']['stepdown']['count'] = count($diagwin5['stepdown']);    
    foreach( $diagwin5['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin5']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin5']['z1updown']['match'] = 0;
    $report_data['diagwin5']['z1updown']['count'] = count($diagwin5['z1updown']);    
    foreach( $diagwin5['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin5']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin5']['z2updown']['match'] = 0;
    $report_data['diagwin5']['z2updown']['count'] = count($diagwin5['z2updown']);    
    foreach( $diagwin5['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin5']['z2updown']['match']++;
	}
    }
    /********************DIAGWIN-10*******************************/
  $diagwin10 = $report_numbers['diagwin10'];
    
    $report_data['diagwin10']['stepup']['match'] = 0;
    $report_data['diagwin10']['stepup']['count'] = count($diagwin10['stepup']);    
    foreach( $diagwin10['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin10']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin10']['stepdown']['match'] = 0;
    $report_data['diagwin10']['stepdown']['count'] = count($diagwin10['stepdown']);    
    foreach( $diagwin10['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin10']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin10']['z1updown']['match'] = 0;
    $report_data['diagwin10']['z1updown']['count'] = count($diagwin10['z1updown']);    
    foreach( $diagwin10['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin10']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin10']['z2updown']['match'] = 0;
    $report_data['diagwin10']['z2updown']['count'] = count($diagwin10['z2updown']);    
    foreach( $diagwin10['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin10']['z2updown']['match']++;
	}
    }
     /********************DIAGWIN-20*******************************/
  $diagwin20 = $report_numbers['diagwin20'];
    
    $report_data['diagwin20']['stepup']['match'] = 0;
    $report_data['diagwin20']['stepup']['count'] = count($diagwin20['stepup']);    
    foreach( $diagwin20['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin20']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin20']['stepdown']['match'] = 0;
    $report_data['diagwin20']['stepdown']['count'] = count($diagwin20['stepdown']);    
    foreach( $diagwin20['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin20']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin20']['z1updown']['match'] = 0;
    $report_data['diagwin20']['z1updown']['count'] = count($diagwin20['z1updown']);    
    foreach( $diagwin20['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin20']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin20']['z2updown']['match'] = 0;
    $report_data['diagwin20']['z2updown']['count'] = count($diagwin20['z2updown']);    
    foreach( $diagwin20['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin20']['z2updown']['match']++;
	}
    }
        /********************DIAGWIN-50*******************************/
  $diagwin50 = $report_numbers['diagwin50'];
    
    $report_data['diagwin50']['stepup']['match'] = 0;
    $report_data['diagwin50']['stepup']['count'] = count($diagwin50['stepup']);    
    foreach( $diagwin50['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin50']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin50']['stepdown']['match'] = 0;
    $report_data['diagwin50']['stepdown']['count'] = count($diagwin50['stepdown']);    
    foreach( $diagwin50['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin50']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin50']['z1updown']['match'] = 0;
    $report_data['diagwin50']['z1updown']['count'] = count($diagwin50['z1updown']);    
    foreach( $diagwin50['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin50']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin50']['z2updown']['match'] = 0;
    $report_data['diagwin50']['z2updown']['count'] = count($diagwin50['z2updown']);    
    foreach( $diagwin50['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin50']['z2updown']['match']++;
	}
    }
    
          /********************DIAGWIN-100*******************************/
  $diagwin100 = $report_numbers['diagwin100'];
    
    $report_data['diagwin100']['stepup']['match'] = 0;
    $report_data['diagwin100']['stepup']['count'] = count($diagwin100['stepup']);    
    foreach( $diagwin100['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin100']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin100']['stepdown']['match'] = 0;
    $report_data['diagwin100']['stepdown']['count'] = count($diagwin100['stepdown']);    
    foreach( $diagwin100['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin100']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin100']['z1updown']['match'] = 0;
    $report_data['diagwin100']['z1updown']['count'] = count($diagwin100['z1updown']);    
    foreach( $diagwin100['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin100']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin100']['z2updown']['match'] = 0;
    $report_data['diagwin100']['z2updown']['count'] = count($diagwin100['z2updown']);    
    foreach( $diagwin100['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin100']['z2updown']['match']++;
	}
    }
     
    return $report_data; 
}

function lotto_patterns_autopicks_efficiency_report_data_spiral($lottery_name, $draw_num, $draw_num_val){
    $report_numbers = get_autopicks_efficiency_report_numbers_spiral($lottery_name, $draw_num, $draw_num_val);
   
    $report_data = array();
    $report_data['draw_details'] = $report_numbers['draw_details'];
    
    $lotto_results = $report_numbers['lotto_results'];
    /*********************AUTOPICKs***********************************/
    $autopicks = $report_numbers['autopick_nbrs'];    
    
    $report_data['autopicks']['diagonal']['match'] = 0;
    $report_data['autopicks']['diagonal']['count'] = count($autopicks['diagonal']);    
    foreach( $autopicks['diagonal'] as $num_d){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['diagonal']['match']++;
	}
    }
    
    $report_data['autopicks']['ladder']['match'] = 0;
    $report_data['autopicks']['ladder']['count'] = count($autopicks['ladder']);    
    foreach( $autopicks['ladder'] as $num_l){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['ladder']['match']++;
	}
    }
    /*********************DIAGWIN-5***********************************/
    $diagwin5 = $report_numbers['diagwin5'];
    
    $report_data['diagwin5']['pillar']['match']=0;
    $report_data['diagwin5']['pillar']['count']=count($diagwin5['pillar']);    
    foreach( $diagwin5['pillar'] as $num_p){
	if (in_array($num_p, $lotto_results)){
	   $report_data['diagwin5']['pillar']['match']++;
	}
    }
        
    $report_data['diagwin5']['stepup']['match'] = 0;
    $report_data['diagwin5']['stepup']['count'] = count($diagwin5['stepup']);    
    foreach( $diagwin5['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin5']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin5']['stepdown']['match'] = 0;
    $report_data['diagwin5']['stepdown']['count'] = count($diagwin5['stepdown']);    
    foreach( $diagwin5['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin5']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin5']['z1updown']['match'] = 0;
    $report_data['diagwin5']['z1updown']['count'] = count($diagwin5['z1updown']);    
    foreach( $diagwin5['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin5']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin5']['z2updown']['match'] = 0;
    $report_data['diagwin5']['z2updown']['count'] = count($diagwin5['z2updown']);    
    foreach( $diagwin5['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin5']['z2updown']['match']++;
	}
    }
    /********************DIAGWIN-10*******************************/
  $diagwin10 = $report_numbers['diagwin10'];
    
  $report_data['diagwin10']['pillar']['match']=0;
    $report_data['diagwin10']['pillar']['count']=count($diagwin10['pillar']);    
    foreach( $diagwin10['pillar'] as $num_p){
	if (in_array($num_p, $lotto_results)){
	   $report_data['diagwin10']['pillar']['match']++;
	}
    }
    
    $report_data['diagwin10']['stepup']['match'] = 0;
    $report_data['diagwin10']['stepup']['count'] = count($diagwin10['stepup']);    
    foreach( $diagwin10['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin10']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin10']['stepdown']['match'] = 0;
    $report_data['diagwin10']['stepdown']['count'] = count($diagwin10['stepdown']);    
    foreach( $diagwin10['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin10']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin10']['z1updown']['match'] = 0;
    $report_data['diagwin10']['z1updown']['count'] = count($diagwin10['z1updown']);    
    foreach( $diagwin10['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin10']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin10']['z2updown']['match'] = 0;
    $report_data['diagwin10']['z2updown']['count'] = count($diagwin10['z2updown']);    
    foreach( $diagwin10['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin10']['z2updown']['match']++;
	}
    }
     /********************DIAGWIN-20*******************************/
  $diagwin20 = $report_numbers['diagwin20'];
    
   $report_data['diagwin20']['pillar']['match']=0;
    $report_data['diagwin20']['pillar']['count']=count($diagwin20['pillar']);    
    foreach( $diagwin20['pillar'] as $num_p){
	if (in_array($num_p, $lotto_results)){
	   $report_data['diagwin20']['pillar']['match']++;
	}
    }
        
    $report_data['diagwin20']['stepup']['match'] = 0;
    $report_data['diagwin20']['stepup']['count'] = count($diagwin20['stepup']);    
    foreach( $diagwin20['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin20']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin20']['stepdown']['match'] = 0;
    $report_data['diagwin20']['stepdown']['count'] = count($diagwin20['stepdown']);    
    foreach( $diagwin20['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin20']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin20']['z1updown']['match'] = 0;
    $report_data['diagwin20']['z1updown']['count'] = count($diagwin20['z1updown']);    
    foreach( $diagwin20['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin20']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin20']['z2updown']['match'] = 0;
    $report_data['diagwin20']['z2updown']['count'] = count($diagwin20['z2updown']);    
    foreach( $diagwin20['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin20']['z2updown']['match']++;
	}
    }
        /********************DIAGWIN-50*******************************/
  $diagwin50 = $report_numbers['diagwin50'];
    
  $report_data['diagwin50']['pillar']['match']=0;
    $report_data['diagwin50']['pillar']['count']=count($diagwin50['pillar']);    
    foreach( $diagwin50['pillar'] as $num_p){
	if (in_array($num_p, $lotto_results)){
	   $report_data['diagwin50']['pillar']['match']++;
	}
    }
  
    $report_data['diagwin50']['stepup']['match'] = 0;
    $report_data['diagwin50']['stepup']['count'] = count($diagwin50['stepup']);    
    foreach( $diagwin50['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin50']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin50']['stepdown']['match'] = 0;
    $report_data['diagwin50']['stepdown']['count'] = count($diagwin50['stepdown']);    
    foreach( $diagwin50['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin50']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin50']['z1updown']['match'] = 0;
    $report_data['diagwin50']['z1updown']['count'] = count($diagwin50['z1updown']);    
    foreach( $diagwin50['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin50']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin50']['z2updown']['match'] = 0;
    $report_data['diagwin50']['z2updown']['count'] = count($diagwin50['z2updown']);    
    foreach( $diagwin50['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin50']['z2updown']['match']++;
	}
    }
    
          /********************DIAGWIN-100*******************************/
  $diagwin100 = $report_numbers['diagwin100'];
    
  $report_data['diagwin100']['pillar']['match']=0;
    $report_data['diagwin100']['pillar']['count']=count($diagwin100['pillar']);    
    foreach( $diagwin100['pillar'] as $num_p){
	if (in_array($num_p, $lotto_results)){
	   $report_data['diagwin100']['pillar']['match']++;
	}
    }  
  
    $report_data['diagwin100']['stepup']['match'] = 0;
    $report_data['diagwin100']['stepup']['count'] = count($diagwin100['stepup']);    
    foreach( $diagwin100['stepup'] as $num_su){
	if (in_array($num_su, $lotto_results)){
	   $report_data['diagwin100']['stepup']['match']++;
	}
    }
    
    $report_data['diagwin100']['stepdown']['match'] = 0;
    $report_data['diagwin100']['stepdown']['count'] = count($diagwin100['stepdown']);    
    foreach( $diagwin100['stepdown'] as $num_sd){
	if (in_array($num_sd, $lotto_results)){
	   $report_data['diagwin100']['stepdown']['match']++;
	}
    }
  
    $report_data['diagwin100']['z1updown']['match'] = 0;
    $report_data['diagwin100']['z1updown']['count'] = count($diagwin100['z1updown']);    
    foreach( $diagwin100['stepdown'] as $num_z1ud){
	if (in_array($num_z1ud, $lotto_results)){
	   $report_data['diagwin100']['z1updown']['match']++;
	}
    }
    
     $report_data['diagwin100']['z2updown']['match'] = 0;
    $report_data['diagwin100']['z2updown']['count'] = count($diagwin100['z2updown']);    
    foreach( $diagwin100['z2updown'] as $num_z2ud){
	if (in_array($num_z2ud, $lotto_results)){
	   $report_data['diagwin100']['z2updown']['match']++;
	}
    }
     
    return $report_data; 
}
function lotto_patterns_autopicks_efficiency_report_data_t($lottery_name, $draw_num, $draw_num_val){
    $report_numbers = get_autopicks_efficiency_report_numbers($lottery_name, $draw_num, $draw_num_val);
    $report_data = array();
    $report_data['draw_details'] = $report_numbers['draw_details'];
    
    $lotto_results = $report_numbers['lotto_results'];
    /*********************AUTOPICKs***********************************/
    $autopicks = $report_numbers['autopick_nbrs'];    
    
    $report_data['autopicks']['diagonal']['match'] = 0;
    $report_data['autopicks']['diagonal']['count'] = count($autopicks['diagonal']);    
    foreach( $autopicks['diagonal'] as $num_d){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['diagonal']['match']++;
	}
    }
    
    $report_data['autopicks']['ladder']['match'] = 0;
    $report_data['autopicks']['ladder']['count'] = count($autopicks['ladder']);    
    foreach( $autopicks['ladder'] as $num_l){
	if (in_array($num_d, $lotto_results)){
	   $report_data['autopicks']['ladder']['match']++;
	}
    }
    
    /*********************Diagwin5***********************************/
    $diagwin5 = $report_numbers['diagwin5'];
    
    $report_data['diagwin5']['stepup'] = diagwin_numbers_validate($diagwin5['stepup'], $lotto_results, 'stepup');
    $report_data['diagwin5']['stepdown'] = diagwin_numbers_validate($diagwin5['stepdown'], $lotto_results, 'stepdown');
    $report_data['diagwin5']['z1updown'] = diagwin_numbers_validate($diagwin5['z1updown'], $lotto_results, 'z1updown');
    $report_data['diagwin5']['z2updown'] = diagwin_numbers_validate($diagwin5['z2updown'], $lotto_results, 'z2updown');
    
     /*********************Diagwin10***********************************/
    $diagwin10 = $report_numbers['diagwin10'];
    
    $report_data['diagwin10']['stepup'] = diagwin_numbers_validate($diagwin10['stepup'], $lotto_results, 'stepup');
    $report_data['diagwin10']['stepdown'] = diagwin_numbers_validate($diagwin10['stepdown'], $lotto_results, 'stepdown');
    $report_data['diagwin10']['z1updown'] = diagwin_numbers_validate($diagwin10['z1updown'], $lotto_results, 'z1updown');
    $report_data['diagwin10']['z2updown'] = diagwin_numbers_validate($diagwin10['z2updown'], $lotto_results, 'z2updown');
    
     /*********************Diagwin20***********************************/
    $diagwin20 = $report_numbers['diagwin20'];
    
    $report_data['diagwin20']['stepup'] = diagwin_numbers_validate($diagwin20['stepup'], $lotto_results, 'stepup');
    $report_data['diagwin20']['stepdown'] = diagwin_numbers_validate($diagwin20['stepdown'], $lotto_results, 'stepdown');
    $report_data['diagwin20']['z1updown'] = diagwin_numbers_validate($diagwin20['z1updown'], $lotto_results, 'z1updown');
    $report_data['diagwin20']['z2updown'] = diagwin_numbers_validate($diagwin20['z2updown'], $lotto_results, 'z2updown');
    
     /*********************Diagwin50***********************************/
    $diagwin50 = $report_numbers['diagwin50'];
    
    $report_data['diagwin50']['stepup'] = diagwin_numbers_validate($diagwin50['stepup'], $lotto_results, 'stepup');
    $report_data['diagwin50']['stepdown'] = diagwin_numbers_validate($diagwin50['stepdown'], $lotto_results, 'stepdown');
    $report_data['diagwin50']['z1updown'] = diagwin_numbers_validate($diagwin50['z1updown'], $lotto_results, 'z1updown');
    $report_data['diagwin50']['z2updown'] = diagwin_numbers_validate($diagwin50['z2updown'], $lotto_results, 'z2updown');
   
     /*********************Diagwin100***********************************/
    $diagwin100 = $report_numbers['diagwin100'];
    
    $report_data['diagwin100']['stepup'] = diagwin_numbers_validate($diagwin100['stepup'], $lotto_results, 'stepup');
    $report_data['diagwin100']['stepdown'] = diagwin_numbers_validate($diagwin100['stepdown'], $lotto_results, 'stepdown');
    $report_data['diagwin100']['z1updown'] = diagwin_numbers_validate($diagwin100['z1updown'], $lotto_results, 'z1updown');
    $report_data['diagwin100']['z2updown'] = diagwin_numbers_validate($diagwin100['z2updown'], $lotto_results, 'z2updown');
    
     return $report_data;
}

function get_autopicks_efficiency_report_numbers($lottery_name, $draw_num, $draw_num_val){
    $draw = lotto_keno_result_by_draw_num($draw_num);
    
    
    $draw_val = lotto_keno_result_by_draw_num($draw_num_val);
    
    $draw_results_val=array();
    for($i=1; $i <= 20; $i++){
	array_push($draw_results_val, $draw_val['n'.$i]);
    }
    
    $autopicks = lotto_bets_autopick($lottery_name, $draw_num);
    $autopicks_efficiency_report_numbers = array(
	'draw_details'=>array(
	    'draw_num'=>$draw_num,
	    'draw_time'=>date('h:i', $draw['draw_date']),
	    'draw_num_val'=>$draw_num_val
	    ),
	'lotto_results'=>$draw_results_val,
	'autopick_nbrs'=>array(
	    'diagonal'=>$autopicks['diagonal'],
	    'ladder'=>$autopicks['ladder']
	    ),
	'diagwin5'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 5, 10),
	'diagwin10'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 10, 10),
	'diagwin20'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 20, 10),
	'diagwin50'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 50, 10),
	'diagwin100'=>lotto_patterns_diag_win_efficiency_numbers($lottery_name, $draw_num, 100, 10),
    );
    
    return $autopicks_efficiency_report_numbers;
}

function get_autopicks_efficiency_report_numbers_spiral($lottery_name, $draw_num, $draw_num_val){
    $draw = lotto_keno_result_by_draw_num($draw_num);
    
    
    $draw_val = lotto_keno_result_by_draw_num($draw_num_val);
    
    $draw_results_val=array();
    for($i=1; $i <= 20; $i++){
	array_push($draw_results_val, $draw_val['n'.$i]);
    }
    
    $autopicks = lotto_bets_autopick($lottery_name, $draw_num);
    $autopicks_efficiency_report_numbers = array(
	'draw_details'=>array(
	    'draw_num'=>$draw_num,
	    'draw_time'=>date('h:i', $draw['draw_date']),
	    'draw_num_val'=>$draw_num_val
	    ),
	'lotto_results'=>$draw_results_val,
	'autopick_nbrs'=>array(
	    'diagonal'=>$autopicks['diagonal'],
	    'ladder'=>$autopicks['ladder']
	    ),
	'diagwin5'=>lotto_patterns_diag_win_efficiency_numbers_spiral($lottery_name, $draw_num, 5, 10),
	'diagwin10'=>lotto_patterns_diag_win_efficiency_numbers_spiral($lottery_name, $draw_num, 10, 10),
	'diagwin20'=>lotto_patterns_diag_win_efficiency_numbers_spiral($lottery_name, $draw_num, 20, 10),
	'diagwin50'=>lotto_patterns_diag_win_efficiency_numbers_spiral($lottery_name, $draw_num, 50, 10),
	'diagwin100'=>lotto_patterns_diag_win_efficiency_numbers_spiral($lottery_name, $draw_num, 100, 10),
    );
    
    return $autopicks_efficiency_report_numbers;
}


function get_lotto_patterns_autopicks_efficiency_report($lottery_name, $draw_num, $draw_num_val, $num_of_draws){
    $header = "<table><tbody>";
    
    $labels1 = "<tr>";
    $labels1 .="<th></th>";
    $labels1 .="<th colspan='2' >DrawDetails</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='2' >Autopicks</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin5</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin10</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin20</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin50</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin100</th>";
    $labels1 .="</tr>";
    
    $labels2 = "<tr>";
    $labels2 .="<th></th>";
    $labels2 .="<th>Draw#</th><th>DrawTime</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>Diagonal</th><th>Ladder</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="</tr>";
    
    $report = "";
    
    for($i=0; $i < $num_of_draws; $i++){
	$draw_num_i = $draw_num - $i;
	$draw_num_val_i = $draw_num_val - $i;
	$report_data = lotto_patterns_autopicks_efficiency_report_data($lottery_name, $draw_num_i, $draw_num_val_i);
    
	
	$report .= "<tr>";
	$report .="<th>".$i."</th>";

	$report .="<td>".$report_data['draw_details']['draw_num']."</td>";
	$report .="<td>".$report_data['draw_details']['draw_time']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['autopicks']['diagonal']['match']."</td>";
	$report .="<td>".$report_data['autopicks']['ladder']['match']."</td>";
	$report .="<th class='black' ></td>";


	$report .="<td>".$report_data['diagwin5']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin5']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin5']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin5']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin10']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin10']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin10']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin10']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin20']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin20']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin20']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin20']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin50']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin50']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin50']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin50']['z2updown']['match']."</td>";
	$report .="<th class='black' ></td>";


	$report .="<td>".$report_data['diagwin100']['stepup']['match']."</td>";
	$report .="<td>".$report_data['diagwin100']['stepdown']['match']."</td>";
	$report .="<td>".$report_data['diagwin100']['z1updown']['match']."</td>";
	$report .="<td>".$report_data['diagwin100']['z2updown']['match']."</td>";

	$report .="</tr>";
	
    }
 
    $footer .= "</tbody></table>";
    
    $autopicks_efficiency_report = $header.$labels1.$labels2.$report.$footer;
    
    return $autopicks_efficiency_report;
}

function get_lotto_patterns_autopicks_efficiency_report_t($lottery_name, $draw_num, $draw_num_val, $num_of_draws){
    $header = "<table><tbody>";
    
    $labels1 = "<tr>";
    $labels1 .="<th></th>";
    $labels1 .="<th colspan='2' >DrawDetails</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='2' >Autopicks</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin5</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin10</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin20</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin50</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='4' >DiagWin100</th>";
    $labels1 .="</tr>";
    
    $labels2 = "<tr>";
    $labels2 .="<th></th>";
    $labels2 .="<th>Draw#</th><th>DrawTime</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>Diagonal</th><th>Ladder</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="</tr>";
    
    $report = "";
    
    for($i=0; $i < $num_of_draws; $i++){
	$draw_num_i = $draw_num - $i;
	$draw_num_val_i = $draw_num_val - $i;
	$report_data = lotto_patterns_autopicks_efficiency_report_data($lottery_name, $draw_num_i, $draw_num_val_i);
	$report_data_t = lotto_patterns_autopicks_efficiency_report_data_t($lottery_name, $draw_num_i, $draw_num_val_i);
	
	$report .= "<tr>";
	$report .="<th>".$i."</th>";

	$report .="<td>".$report_data['draw_details']['draw_num']."</td>";
	$report .="<td>".$report_data['draw_details']['draw_time']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['autopicks']['diagonal']['match']."</td>";
	$report .="<td>".$report_data['autopicks']['ladder']['match']."</td>";
	$report .="<th class='black' ></td>";


	$report .="<td>".$report_data['diagwin5']['stepup']['match']."(".$report_data_t['diagwin5']['stepup']['match'];
	$report .= ($report_data_t['diagwin5']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_t['diagwin5']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin5']['stepdown']['match']."(".$report_data_t['diagwin5']['stepdown']['match'];
	$report .= ($report_data_t['diagwin5']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin5']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin5']['z1updown']['match']."(".$report_data_t['diagwin5']['z1updown']['match'];
	$report .= ($report_data_t['diagwin5']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin5']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin5']['z2updown']['match']."(".$report_data_t['diagwin5']['z2updown']['match'];
	$report .=($report_data_t['diagwin5']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin5']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin10']['stepup']['match']."(".$report_data_t['diagwin10']['stepup']['match'];
	$report .= ($report_data_t['diagwin10']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_t['diagwin10']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin10']['stepdown']['match']."(".$report_data_t['diagwin10']['stepdown']['match'];
	$report .= ($report_data_t['diagwin10']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin10']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin10']['z1updown']['match']."(".$report_data_t['diagwin10']['z1updown']['match'];
	$report .= ($report_data_t['diagwin10']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin10']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin10']['z2updown']['match']."(".$report_data_t['diagwin10']['z2updown']['match'];
	$report .=($report_data_t['diagwin10']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin10']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin20']['stepup']['match']."(".$report_data_t['diagwin20']['stepup']['match'];
	$report .= ($report_data_t['diagwin20']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_t['diagwin20']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin20']['stepdown']['match']."(".$report_data_t['diagwin20']['stepdown']['match'];
	$report .= ($report_data_t['diagwin20']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin20']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin20']['z1updown']['match']."(".$report_data_t['diagwin20']['z1updown']['match'];
	$report .= ($report_data_t['diagwin20']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin20']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin20']['z2updown']['match']."(".$report_data_t['diagwin20']['z2updown']['match'];
	$report .=($report_data_t['diagwin20']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin20']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin50']['stepup']['match']."(".$report_data_t['diagwin50']['stepup']['match'];
	$report .= ($report_data_t['diagwin50']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_t['diagwin50']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin50']['stepdown']['match']."(".$report_data_t['diagwin50']['stepdown']['match'];
	$report .= ($report_data_t['diagwin50']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin50']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin50']['z1updown']['match']."(".$report_data_t['diagwin50']['z1updown']['match'];
	$report .= ($report_data_t['diagwin50']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin50']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin50']['z2updown']['match']."(".$report_data_t['diagwin50']['z2updown']['match'];
	$report .=($report_data_t['diagwin50']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin50']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['diagwin100']['stepup']['match']."(".$report_data_t['diagwin100']['stepup']['match'];
	$report .= ($report_data_t['diagwin100']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_t['diagwin100']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin100']['stepdown']['match']."(".$report_data_t['diagwin100']['stepdown']['match'];
	$report .= ($report_data_t['diagwin100']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin100']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin100']['z1updown']['match']."(".$report_data_t['diagwin100']['z1updown']['match'];
	$report .= ($report_data_t['diagwin100']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin100']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin100']['z2updown']['match']."(".$report_data_t['diagwin100']['z2updown']['match'];
	$report .=($report_data_t['diagwin100']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_t['diagwin100']['z2updown']['count'].")</td>";
	
	$report .="</tr>";
	
    }
 
    $footer .= "</tbody></table>";
    
    $autopicks_efficiency_report = $header.$labels1.$labels2.$report.$footer;
    
    return $autopicks_efficiency_report;
}
function ajx_autopicks_efficiency_report($form, $form_state){
    $draw_num = $form_state['values']['draw_number'];
    $draw_num_val = $draw_num + 1;
    $num_of_draws = $form_state['values']['num_of_draws'];
    
    $autopicks_efficiency_report = get_lotto_patterns_autopicks_efficiency_report_t("lotto_keno", $draw_num, $draw_num_val, $num_of_draws);
    $autopicks_efficiency_report_spiral = get_lotto_patterns_autopicks_efficiency_report_spiral("lotto_keno", $draw_num, $draw_num_val, $num_of_draws);
    
    $form['efficiency']['efficiency_report']['report']['#markup']=$autopicks_efficiency_report;
    $form['efficiency']['efficiency_report']['report_spiral']['report']['#markup']=$autopicks_efficiency_report_spiral;
    

    return $form['efficiency']['efficiency_report'];
}


function diagwin_numbers_validate($diagwin_nbrs, $lotto_results, $category, $number_offset=1){
    $validation_data = array(
	'match'=>0,
	'count'=>count($diagwin_nbrs)
    );
    switch($category){
	case 'stepup':
	    foreach($diagwin_nbrs as $num_su){
		$corresponding_num = $num_su + $number_offset;
		if ($corresponding_num <= 80){
		    if(in_array($corresponding_num, $lotto_results)){
			$validation_data['match']++;
		    }
		}
	    }
	    break;
	case 'stepdown':
	    foreach($diagwin_nbrs as $num_sd){
		$corresponding_num = $num_sd - $number_offset;
		if ($corresponding_num > 0){
		    if(in_array($corresponding_num, $lotto_results)){
			$validation_data['match']++;
		    }
		}
	    }
	    break;
	case 'z1updown':
	    $i=1;
	    foreach($diagwin_nbrs as $num_z1){
		if ($i == 1){
		    $corresponding_num = $num_z1 + $number_offset;
		    if ($corresponding_num <= 80 ){
			if(in_array($corresponding_num, $lotto_results)){
			    $validation_data['match']++;
			}
		    }
		    $i = 0;
		} elseif ($i == 0){
		    $corresponding_num = $num_z1 - $number_offset;
		    if ($corresponding_num > 0){
			if(in_array($corresponding_num, $lotto_results)){
			    $validation_data['match']++;
			}
		    }
		    $i = 1;		    
		}		
	    }
	    break;
	case 'z2updown':
	    $i = 0;
	    foreach($diagwin_nbrs as $num_z2){
		if ($i == 1){
		    $corresponding_num = $num_z2 + $number_offset;
		    if ($corresponding_num <= 80 ){
			if(in_array($corresponding_num, $lotto_results)){
			    $validation_data['match']++;
			}
		    }
		    $i = 0;
		} elseif ($i == 0){
		    $corresponding_num = $num_z2 - $number_offset;
		    if ($corresponding_num > 0){
			if(in_array($corresponding_num, $lotto_results)){
			    $validation_data['match']++;
			}
		    }
		    $i = 1;		    
		}		
	    }
	    break;
    }
    
    return $validation_data;
}

function get_lotto_patterns_autopicks_efficiency_report_spiral($lottery_name, $draw_num, $draw_num_val, $num_of_draws){
    
    $header = "<table><tbody>";
    
    $labels1 = "<tr>";
    $labels1 .="<th></th>";
    $labels1 .="<th colspan='2' >DrawDetails</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='2' >Autopicks</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='5' >DiagWin5</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='5' >DiagWin10</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='5' >DiagWin20</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='5' >DiagWin50</th>";
    $labels1 .="<th class='black' ></th>";
    $labels1 .="<th colspan='5' >DiagWin100</th>";
    $labels1 .="</tr>";
    
    $labels2 = "<tr>";
    $labels2 .="<th></th>";
    $labels2 .="<th>Draw#</th><th>DrawTime</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>Diagonal</th><th>Ladder</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="<th class='black' ></th>";
    $labels2 .="<th>PillarWin</th><th>StepUp</th><th>StepDown</th><th>Z1-Up-Down</th><th>Z2-Up-Down</th>";
    $labels2 .="</tr>";
    
    $report = "";
    
    for($i=0; $i < $num_of_draws; $i++){
	$draw_num_i = $draw_num - $i;
	$draw_num_val_i = $draw_num_val - $i;
	$report_data = lotto_patterns_autopicks_efficiency_report_data($lottery_name, $draw_num_i, $draw_num_val_i);
	$report_data_spiral = lotto_patterns_autopicks_efficiency_report_data_spiral($lottery_name, $draw_num_i, $draw_num_val_i);
	
	$report .= "<tr>";
	$report .="<th>".$i."</th>";

	$report .="<td>".$report_data['draw_details']['draw_num']."</td>";
	$report .="<td>".$report_data['draw_details']['draw_time']."</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data['autopicks']['diagonal']['match']."</td>";
	$report .="<td>".$report_data['autopicks']['ladder']['match']."</td>";
	$report .="<th class='black' ></td>";
	
	$report .="<td>".$report_data_spiral['diagwin5']['pillar']['match'];
	$report .=($report_data_spiral['diagwin5']['pillar']['count'] == 10) ?  "</td>" : " ( ".$report_data_spiral['diagwin5']['pillar']['count'].")</td>";
	$report .="<td>".$report_data['diagwin5']['stepup']['match']."(".$report_data_spiral['diagwin5']['stepup']['match'];
	$report .= ($report_data_spiral['diagwin5']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_spiral['diagwin5']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin5']['stepdown']['match']."(".$report_data_spiral['diagwin5']['stepdown']['match'];
	$report .= ($report_data_spiral['diagwin5']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin5']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin5']['z1updown']['match']."(".$report_data_spiral['diagwin5']['z1updown']['match'];
	$report .= ($report_data_spiral['diagwin5']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin5']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin5']['z2updown']['match']."(".$report_data_spiral['diagwin5']['z2updown']['match'];
	$report .=($report_data_spiral['diagwin5']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin5']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data_spiral['diagwin10']['pillar']['match'];
	$report .=($report_data_spiral['diagwin10']['pillar']['count'] == 10) ?  "</td>" : " ( ".$report_data_spiral['diagwin10']['pillar']['count'].")</td>";
	$report .="<td>".$report_data['diagwin10']['stepup']['match']."(".$report_data_spiral['diagwin10']['stepup']['match'];
	$report .= ($report_data_spiral['diagwin10']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_spiral['diagwin10']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin10']['stepdown']['match']."(".$report_data_spiral['diagwin10']['stepdown']['match'];
	$report .= ($report_data_spiral['diagwin10']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin10']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin10']['z1updown']['match']."(".$report_data_spiral['diagwin10']['z1updown']['match'];
	$report .= ($report_data_spiral['diagwin10']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin10']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin10']['z2updown']['match']."(".$report_data_spiral['diagwin10']['z2updown']['match'];
	$report .=($report_data_spiral['diagwin10']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin10']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";
	
	$report .="<td>".$report_data_spiral['diagwin20']['pillar']['match'];
	$report .=($report_data_spiral['diagwin20']['pillar']['count'] == 10) ?  "</td>" : " ( ".$report_data_spiral['diagwin20']['pillar']['count'].")</td>";
	$report .="<td>".$report_data['diagwin20']['stepup']['match']."(".$report_data_spiral['diagwin20']['stepup']['match'];
	$report .= ($report_data_spiral['diagwin20']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_spiral['diagwin20']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin20']['stepdown']['match']."(".$report_data_spiral['diagwin20']['stepdown']['match'];
	$report .= ($report_data_spiral['diagwin20']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin20']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin20']['z1updown']['match']."(".$report_data_spiral['diagwin20']['z1updown']['match'];
	$report .= ($report_data_spiral['diagwin20']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin20']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin20']['z2updown']['match']."(".$report_data_spiral['diagwin20']['z2updown']['match'];
	$report .=($report_data_spiral['diagwin20']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin20']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data_spiral['diagwin50']['pillar']['match'];
	$report .=($report_data_spiral['diagwin50']['pillar']['count'] == 10) ?  "</td>" : " ( ".$report_data_spiral['diagwin50']['pillar']['count'].")</td>";
	$report .="<td>".$report_data['diagwin50']['stepup']['match']."(".$report_data_spiral['diagwin50']['stepup']['match'];
	$report .= ($report_data_spiral['diagwin50']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_spiral['diagwin50']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin50']['stepdown']['match']."(".$report_data_spiral['diagwin50']['stepdown']['match'];
	$report .= ($report_data_spiral['diagwin50']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin50']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin50']['z1updown']['match']."(".$report_data_spiral['diagwin50']['z1updown']['match'];
	$report .= ($report_data_spiral['diagwin50']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin50']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin50']['z2updown']['match']."(".$report_data_spiral['diagwin50']['z2updown']['match'];
	$report .=($report_data_spiral['diagwin50']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin50']['z2updown']['count'].")</td>";
	$report .="<th class='black' ></td>";

	$report .="<td>".$report_data_spiral['diagwin100']['pillar']['match'];
	$report .=($report_data_spiral['diagwin100']['pillar']['count'] == 10) ?  "</td>" : " ( ".$report_data_spiral['diagwin100']['pillar']['count'].")</td>";
	$report .="<td>".$report_data['diagwin100']['stepup']['match']."(".$report_data_spiral['diagwin100']['stepup']['match'];
	$report .= ($report_data_spiral['diagwin100']['stepup']['count'] == 10) ?  ")</td>" : " / ".$report_data_spiral['diagwin100']['stepup']['count'].")</td>";
	$report .="<td>".$report_data['diagwin100']['stepdown']['match']."(".$report_data_spiral['diagwin100']['stepdown']['match'];
	$report .= ($report_data_spiral['diagwin100']['stepdown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin100']['stepdown']['count'].")</td>";
	$report .= "<td>".$report_data['diagwin100']['z1updown']['match']."(".$report_data_spiral['diagwin100']['z1updown']['match'];
	$report .= ($report_data_spiral['diagwin100']['z1updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin100']['z1updown']['count'].")</td>";
	$report .="<td>".$report_data['diagwin100']['z2updown']['match']."(".$report_data_spiral['diagwin100']['z2updown']['match'];
	$report .=($report_data_spiral['diagwin100']['z2updown']['count'] == 10) ?   ")</td>" : " / ".$report_data_spiral['diagwin100']['z2updown']['count'].")</td>";
	
	$report .="</tr>";
	
    }
 
    $footer .= "</tbody></table>";
    
    $autopicks_efficiency_report = $header.$labels1.$labels2.$report.$footer;
    
    return $autopicks_efficiency_report;
    
    
    
    
    
    
}
?>
