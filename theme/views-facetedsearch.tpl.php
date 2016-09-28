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
      facets           : { <?php print $views_facetedsearch_facets; ?> },
      resultSelector   : '#view_facetedsearch_results',
      facetSelector    : '#view_facetedsearch_facets',
      resultTemplate   : item_template,
      enablePagination : <?php print $view->style_options['views_facetedsearch_enable_pagination'] ? 'true' : 'false' ?>,
      paginationCount  : <?php print $view->style_options['views_facetedsearch_pagination_count']  ? 
                                       $view->style_options['views_facetedsearch_pagination_count'] : '0' ?>,
      orderByOptions   : {<?php print $views_facetedsearch_facetorders ?>, 'RANDOM': 'Random'}
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