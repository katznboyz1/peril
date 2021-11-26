# peril

*A language learning trivia website that allows users to fully customize the questions that are asked. It also features a competitive mode where the users can compete for points in a game similar to Jeopardy.*

![](https://i.imgur.com/1aGemxV.png?raw=true)

*The current UI progress. This will change in the future, and it is only a placeholder.*

## Languages:

- French

- Japanese (work in progress)

## TODO:

- Add a Japanese Language quiz sheet.

- Fix the UI to look neater.

## Credits:

- https://github.com/pquentin/wiktionary-translations/

- https://github.com/curl/curl

- https://github.com/ianmackinnon/inflect

- https://github.com/twbs/bootstrap

- https://github.com/jquery/jquery

- https://github.com/popperjs/popper-core

- https://github.com/nih-at/libzip

- https://ankiweb.net/shared/info/1552733819

## Build From Scratch:

- Clone this repo, then make a new folder in the same directory as the cloned repo called *"peril"*.

- CD into the cloned repo, then run `cmake ../peril`.

- CD into `../peril` and then run `cmake --build .`.

- Run `./peril`. If everything returns 0, then all your files are there!

## Adding A Language

- Check the instructions for creating the C++ language files by going to `cpp_src/fetch_data_LANG_TEMPLATE.cpp` and `cpp_src/fetch_data_LANG_TEMPLATE.hpp`.

- Add your `fetch_data_LANG_XXX_all` function to `cpp_src/main.cpp` in the `main()` function, before the line that says `std::cout << "main() = 0" << endl;`. Preferrably, you should call the function using `std::cout` like the ones above are called to give the user an indication of the language function's status.

- Once you have added your `fetch_data_LANG_XXX.cpp/.hpp` files, add them to `cpp_src/CMakeLists.txt`.

- Create a manifest file in `category_data` using the format `manifest.lang.XXX.json` (you can look at the other manifest files for examples).

- Add your manifest file to the `"quizzes"` field in `category_data/manifest.json`.

- Compile the program, and run it to generate all of the proper files.

*Made a new language entry? Create a pull request with your language entry! It would be great to have additional languages available for this program!*