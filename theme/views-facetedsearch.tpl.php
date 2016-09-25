<div id='facets'></div><div id='results'></div>
<script type="text/javascript">
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