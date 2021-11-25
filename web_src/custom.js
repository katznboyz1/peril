document.manifest_data = undefined;

window.onload = function(){

    let category_row_original = document.getElementsByClassName('peril-main-grid-row-category-cost')[0];

    $.getJSON('category_data/manifest.json', function(data_1) {

        document.manifest_data = data_1;

        $.getJSON('category_data/' + document.manifest_data['quizzes'][0], function(data_2) {

            // let this auto-scale by referencing the "api" in the future
            let num_of_rows = data_2['quiz_scores'].length;
            let num_of_categories = 6;
            let height_css = 'calc(100vh/' + String(num_of_rows + 1) + ')';
            let data_2_quiz_data_keys = Object.keys(data_2['quiz_data']);

            for (i = 0; i < document.getElementById('peril-main-board-category-bar').children.length; i++) {

                // escape all chars to prevent xss attacks
                document.getElementById('peril-main-board-category-bar').children[i].children[0].innerHTML = data_2_quiz_data_keys[i];
                document.getElementById('peril-main-board-category-bar').children[i].children[0].style.height = height_css;
            }

            for (i = 1; i < num_of_rows; i++) {

                // clone the node (deep)
                let category_duplicate = category_row_original.cloneNode(true);

                document.getElementById('peril-main-board').appendChild(category_duplicate);
            }

            for (i = 0; i < num_of_rows; i++) {

                let current_parent_node = document.getElementsByClassName('peril-main-grid-row-category-cost')[i];

                for (j = 0; j < num_of_categories; j++) {

                    current_parent_node.children[j].children[0].innerHTML = data_2['quiz_scores'][i];
                    current_parent_node.children[j].children[0].style.height = height_css;
                }
            }
        });
    });
}