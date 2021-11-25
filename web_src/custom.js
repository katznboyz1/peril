window.onload = function(){

    let category_row_original = document.getElementsByClassName('peril-main-grid-row-category-cost')[0];

    $.getJSON('/manifest.json', function(data) {
        // JSON result in `data` variable
    });

    // let this auto-scale by referencing the "api" in the future
    let num_of_rows = 5;
    let num_of_categories = 6; 

    for (i = 1; i < num_of_rows; i++) {

        // clone the node (deep)
        let category_duplicate = category_row_original.cloneNode(true);

        document.getElementById('peril-main-board').appendChild(category_duplicate);
    }

    for (i = 0; i < num_of_rows; i++) {

        let current_parent_node = document.getElementsByClassName('peril-main-grid-row-category-cost')[i];

        for (j = 0; j < num_of_categories; j++) {

            current_parent_node.children[j].children[0].innerHTML = "0000";
        }
    }
}