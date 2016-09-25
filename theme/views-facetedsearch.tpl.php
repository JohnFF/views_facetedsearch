<div id='facets'></div><div id='results'></div>
<script type="text/javascript">
  jQuery(function(){
    var item_template = 
     '<div class=\"item\">' +
       '<p class=\"tags\">' + 
       '<% if (obj.id) {  %><%= obj.id %><% } %>' +
       '<% if (obj.civicrm_contact_source) {  %>, <%= obj.civicrm_contact_source %><% } %>' +
       '<% if (obj.civicrm_contact_display_name) {  %>, <%= obj.civicrm_contact_display_name %><% } %>' +
       '</p>' +
     '</div>';
    settings = { 
      items            : views_facetedsearch_resultitems,
      facets           : {            
        <?php
          $optionsArray = array();
          foreach($view->style_options as $eachOptionKey => $eachOptionValue){
            // Check that the option begins with 'views_facetedsearch_facets_'.
            if (strpos($eachOptionKey, 'views_facetedsearch_facets_') === FALSE){
              continue;
            }
            if ($eachOptionValue == '0'){
              continue;
            }
            $facet = str_replace('views_facetedsearch_facets_', '', $eachOptionKey);
              $optionsArray[] = "'$facet' : '$facet'";
              
          }
          $facetOptionsString = implode(', ', $optionsArray);
          print implode(', ', $optionsArray);
        ?>
      },  
      resultSelector   : '#results',
      facetSelector    : '#facets',
      resultTemplate   : item_template,
      enablePagination : false,
      paginationCount  : 50,
      orderByOptions   : {<?php print $facetOptionsString ?>, 'RANDOM': 'Random'},
      //facetSortOption  : {'civicrm_contact_source': [\"0\", \"1\"]}
    }   

    // use them!
    jQuery.facetelize(settings);
  });
  
  var views_facetedsearch_resultitems = [
  <?php
    $resultCount = count($view->result);
    $resultIndex = 0;
    
    if (count($view->result) > 0){
      $attributeCount = count((array) $view->result[0]);
    }
    
    foreach ($view->result as $resultIndex => $eachResult) {
      $eachResult = (array) $eachResult; // Cast each object into an array.
      $attributeIndex = 0;
      print '{';
      foreach ($eachResult as $attributeKey => $attribute){
        $attribute = $attribute ? $attribute : "NONE";
        print '"' . addslashes($attributeKey) . '" : "' . addslashes($attribute) . '"';
        $attributeIndex++;
        if ($attributeIndex != $attributeCount){
          print ',';
        }
        print "\n";
      }
      print '}';
      $resultIndex ++;
      if ($resultIndex != $resultCount){
        print ",\n";        
      }
    }
  ?>
];
</script>