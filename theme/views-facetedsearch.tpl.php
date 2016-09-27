<div id='view_facetedsearch_facets'></div><div id='view_facetedsearch_results'></div>
<script type="text/javascript">
  jQuery(function(){

    var item_template =
     '<div class=\"item\">' +
       '<p class=\"tags\">' +
       '<% if (obj.id) {  %><%= obj.id %><% } %>' +
       '<% if (obj.source) {  %>, <%= obj.source %><% } %>' +
       '<% if (obj.display_name) {  %>, <%= obj.display_name %><% } %>' +
       '<% if (obj.gender) {  %>, <%= obj.gender %><% } %>' +
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
            //$optionsArray[] = "'$facet' : '$facet'";
            //die(print_r($view->display['default']->handler->options['fields'][$facet], TRUE));
            if (array_key_exists('label', $view->display['default']->handler->options['fields'][$facet])) {
              $label = $view->display['default']->handler->options['fields'][$facet]['label'];
            }
            else {
              $label = $facet;
            }

            $optionsArray[] = "'$facet' : '$label'";
          }
          $facetOptionsString = implode(', ', $optionsArray);
          print $facetOptionsString;
        ?>
      },
      resultSelector   : '#view_facetedsearch_results',
      facetSelector    : '#view_facetedsearch_facets',
      resultTemplate   : item_template,
      enablePagination : <?php print $view->style_options['views_facetedsearch_enable_pagination'] ? 'true' : 'false' ?>,
      paginationCount  : <?php print $view->style_options['views_facetedsearch_pagination_count'] ?>,
      orderByOptions   : {<?php print $facetOptionsString ?>, 'RANDOM': 'Random'}
      //facetSortOption  : {'civicrm_contact_source': [\"0\", \"1\"]}
    }

    // use them!
    jQuery.facetelize(settings);
  });

  var views_facetedsearch_resultitems = [
  <?php
    // Populate the results items from the views data.
    $resultCount = count($view->result);
    $resultIndex = 0;

    if (count($view->style_plugin->rendered_fields) > 0){
      $attributeCount = count((array) $view->style_plugin->rendered_fields[0]);
    }

    foreach ($view->style_plugin->rendered_fields  as $resultIndex => $eachResult) {
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