document.manifest_data = undefined;
document.category_data = undefined;
document.quiz_data = [];

is_first_question = true;

const CATEGORY_DATA_ROUTE = 'category_data/'

window.onload = function(){

    $.getJSON(CATEGORY_DATA_ROUTE + 'manifest.json', function(data_1) {

        document.manifest_data = data_1;

        for (i = 0; i < document.manifest_data['quizzes'].length; i++) {

            let new_dropdown_elem = document.createElement('a');
            new_dropdown_elem.classList.add('dropdown-item');
            new_dropdown_elem.setAttribute('onclick', 'load_trivia_page(' + String(i) + ')');
            new_dropdown_elem.innerHTML = document.manifest_data['quizzes'][i][1];
            document.getElementById('peril-drop-down-menu-options').appendChild(new_dropdown_elem);
        }
    });
}

function load_trivia_page(index) {

    let category_row_original = document.getElementsByClassName('peril-main-grid-row-category-cost')[0];

    $.getJSON(CATEGORY_DATA_ROUTE + document.manifest_data['quizzes'][index][0], function(data_2) {

        document.category_data = data_2;

        // let this auto-scale by referencing the "api" in the future
        let num_of_rows = data_2['quiz_scores'].length;
        let num_of_categories = 6;
        let height_css = 'calc(100vh/' + String(num_of_rows + 1) + ')';
        let data_2_quiz_data_keys = Object.keys(data_2['quiz_data']);

        for (i = 0; i < document.getElementById('peril-main-board-category-bar').children.length; i++) {

            // TODO: escape all chars to prevent xss attacks
            document.getElementById('peril-main-board-category-bar').children[i].children[0].innerHTML = data_2_quiz_data_keys[i].replace('<', '&lt;').replace('>', '&gt;');
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
                current_parent_node.children[j].setAttribute('onclick', 'register_answer_click(' + String(i) + ',' + String(j) + ')');
            }
        }

        document.getElementById('peril-home-page').style.visibility = 'hidden';

        // download the quiz data
        // might want to have a loading icon for this
        for (i = 0; i < data_2_quiz_data_keys.length; i++) {

            $.get(CATEGORY_DATA_ROUTE + document.category_data['quiz_data'][data_2_quiz_data_keys[i]], function(data_3) {

                document.quiz_data.push(data_3.split(/\r?\n/));
            });
        }
    });
}

function register_answer_click(row, col) {

    let num_of_rows = document.category_data['quiz_scores'].length;
    let num_of_categories = 6;

    for (i = 0; i < num_of_rows; i++) {

        let current_parent_node = document.getElementsByClassName('peril-main-grid-row-category-cost')[i];

        for (j = 0; j < num_of_categories; j++) {

            if (i == row && j == col) current_parent_node.children[j].children[0].innerHTML = '';
        }
    }

    document.getElementById('peril-answer-page').style.visibility = 'visible';
    document.getElementById('peril-answer-page-question').innerHTML = document.quiz_data[col][Math.floor(Math.random() * document.quiz_data[col].length)].split(/[|]/)[0];

    if (is_first_question) {

        alert('Click the question to relveal the answer!');

        is_first_question = false;
    }
}

console.log('Want to contribute? Check out the GitHub repo! https://github.com/katznboyz1/peril');