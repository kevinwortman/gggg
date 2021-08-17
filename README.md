# gggg
Gradescope-Googletest Grading Glue (gggg)

This is a lightweight framework for Gradescope autograding of C++ programming assignments.

![Screenshot showing the "make grade" command in action.](https://github.com/kevinwortman/gggg/raw/main/media/make_grade.png)

![Screenshot of the Gradescope autograder results page.](https://github.com/kevinwortman/gggg/raw/main/media/autograder_results.png)


## Architecture

A gggg assignment involves several software services working together.

 * Canvas (or another LMS) announces the assignment to students, and stores canonical grades.
 * GitHub Education manages a private repository for each student team. Each repository is initially a copy of a template repository, containing starter code, created by an instructor. Students submit work by pushing to these repositories.
 * Gradescope manages grading, including automated grading (autograding) and optional subjective grading. Gradescope pushes scores to Canvas.
 * GoogleTest may be used for graded code correctness tests.
 * This gggg project is the glue that connects these components.
   - An instructor specifies how a submission is graded by writing a short Python script, conventionally named `grade.py`. A `grade.py` script uses the `gggg.py` library, which defines an API for declaring submission and rubric policies.
   - Sample `Makefile`s have a `make grade` target. Students run `make grade` locally to preview their grade. The Gradescope autograde runs `make grade` to produce a machine-readable score. 
   - The `make-autograder` program creates an `autograder.zip` needed by Gradescope. An `autograder.zip` contains some very short scripts that tell Gradescope how to prepare a container, run `make grade`, and import the score generated by `grade.py`.

## Detailed Workflow

This section explains what happens in an assignment, in chronological order.

Instructor prepares a class (once per term):
1. Follow the [GitHub Education quickstart instructions](https://docs.github.com/en/education/quickstart) to create an organization for the course, and establish or renew an educator discount.
2. [Create a classroom object in GitHub Education](https://classroom.github.com/classrooms).
3. Add the GradeScope App to the class Canvas space.

Students prepare for a class (once per term):
1. Create GitHub accounts. It is a best practice to assign this as an out-of-class homework assignment. GitHub has a DDoS mitigation that is triggered by a lab's worth of students all creating accounts at the same moment from similar IP addresses.

Instructor creates an assignment:
1. Create a **template repository** inside the GitHub Organization, to hold starter code distributed to students.
   1. In the GitHub web view: create a private repository; suggest no to README; MIT license; and C++ .gitignore.
   2. In Settings: turn on `Template repository`.
   3. Clone the repo to a local machine. Copy files from the `ggg/template-skeleton` directory: `Makefile`, `README.md`, `gggg.py`, `grade.py`, and (if relevant) `timer.hpp`.
2. Create a C++ **solution**, unit tests, Makefile, and `grade.py` script (see the `template-example` directory for a working example). Confirm that `make grade` works and shows a perfect score. Never commit the solution, because students could view it in the git history. The [Gradescope containers run in Ubuntu 18.04](https://gradescope-autograders.readthedocs.io/en/latest/specs/), so ensure that your code can compile and run in that environment.
3. **Archive the solution**. Suggestion: `zip` the repo on the commandline.
4. Modify the `.hpp` and `.cpp` files to become **starter code**; add a TODO comment everywhere that students should edit code; confirm that `make grade` works and shows an imperfect score; and commit+push the starter code.
6. **Archive the starter code**. Suggestion: web view > Code > Download ZIP.
7. Create an **autograder ZIP**. In the terminal, move into the template repo and run the gggg `make-autograder` script. `make-autograder -h` displays usage help. Pass a `-f <filename>` argument for each `<filename>` that students may not modify. The autograder will overwrite these files with starter code to prevent an exploit where a student modifies the tests or grading logic. Example:
   ```
   $ make-autograder -f Makefile -f gggg.py -f grade.py -f product_test.cpp -o autograder.zip
   ```
9. Create a **GitHub Education assignment object**: [classroom.github.com](https://classroom.github.com) > New Assignment > Create Group Assignment (or individual assignment, as the case may be). Suggested settings:
   1. Title: "Project 2", "Lab 3", or similar.
   2. Deadline: blank (Gradescope enforces deadlines)
   3. Individual or Group: self-explanatory
   4. (Group assignment) Name your set of teams: "Project 2 Groups" or similar
   5. (Group assignment) Maximum members per team: 3 (or whatever your class policy is)
   6. Repository visibility: Private (otherwise plagiarism is extremely easy and tempting)
   7. Grant students admin access to their repository: no (these privileges allow students to irreparably break their repos)
   8. Your assignment repository prefix: automatically populates to "project-2" or similar
   9. Add a template repository to give students starter code: Find and use the template repo you created above.
   10. Allow students to use an online IDE: no (default)
   11. (Continue)
   12. Add autograding tests: no (we use Gradescope instead)
   13. Enable feedback pull requests: no (default)
   14. (Create Assignment)
   15. Copy the assignment link, you will need it below (looks like https://classroom.github.com/g/mwO5m1Za).
10. Create a **Canvas assignment object**. This is a lightweight placeholder that only serves to make the deadline visible in Canvas, and the grades available in the Canvas gradebook. (If you do not use Canvas, instead create an assignment in your chosen LMS.)
    1. Decide whether your assignment will be graded solely on the basis of automated `grade.py` scores, or will also include manual subjective scores.
    2. Calculate your maximum score = (max `grade.py` points) + (max manual points)
    3. Canvas > Create Assignment
    4. Points: maximum score calculated above
    5. Submission type: External Tool > Gradescope. Load This Tool In A New Tab: yes 
    6. Allowed Attempts: Limited to 1 (unclear if this is honored)
    7. Assign to: everyone, with your stated deadline. (This deadline will be communicated to students in their calendar view. Gradescope will enforce the deadline.)
11. Create a **Gradescope assignment object**. This is the more substantial assignment where students make submissions, view feedback, and may request regrades.
    1. [gradescope.com](https://www.gradescope.com/) > Course > Assignments > Create New Assignment > Programming Assignment > Next
    2. Assignment Name: same as the Canvas assignment, e.g. "Project 2"
    3. Autograder points: (max `grade.py` points)
    4. Enable Manual Grading: yes iff you include manual subjective scores
    5. Release date: your choice, probably now
    6. Due date: match deadline in Canvas
    7. Enable Group Submission: yes (if this is a group project)
    8. Limit Group Size: match group size in Github Education
    9. Next
    10. Configure Autograder: Upload the `autograder.zip` created above. Wait for the container to finish building.
    11. Test Autograder: Upload the solution archive ZIP you created above, and confirm that it is graded properly. Likewise, confirm that the starter code archive ZIP is graded properly.
    12. Link Canvas: Assignment > Settings > Canvas Assignment: choose your Canvas assignment; click Link
12. Create an **assignment brief (instructions)** and publish it to students. A Canvas Page is best for accessibility and permissions management, but a Google Doc is also acceptable. Include links to:
    1. The Github Classroom invitation URL (looks like https://classroom.github.com/g/mwO5m1Za)
    3. Gradescope Student Center: https://help.gradescope.com/category/cyk4ij2dwi-student-workflow
    5. GitHub guides: https://guides.github.com/
    6. Pro Git book: https://git-scm.com/book/en/v2
    7. David McLaren’s github getting started video: https://www.youtube.com/watch?v=1a5L_xsGIm8

Students work an assignment:
1. Decide on **who is in the team**. This **must** be done out-of-band before the next steps. GitHub Education does not support modifying teams, and there is no interface for instructors to modify a team.
2. The first team member follows the invitation URL (looks like https://classroom.github.com/g/mwO5m1Za) to **create a team** and repository.
3. Subsequent team members, if any, follow the invitation URL and join the team from the previous step. This is necessary for the team members to access the repo, but does not impact who gets credit for the submission. Technically a team could skip this step and do all edits from a single github account, but this is discouraged.
4. **Clone** the repo to local machines.
5. **Develop code**; write, test, and debug. Run `make test` and respond to unit test feedback. Commit+push regularly.
6. **Preview grade**; run `make grade`, respond to feedback, and decide whether to continue working.
7. **Commit+push** the final draft to github.
8. **Submit** the repo to Gradescope. Follow [the instructions](https://help.gradescope.com/article/ccbpppziu9-student-submit-work#code_submissions); submitting a GitHub repo directly is bulletproof, but uploading a ZIP also works. At this step, students indicate their team members if any. This choice determines who gets credit, but has no bearing on repo access.
9. **Confirm** that the Gradescope autograder feedback matches the local `make grade` output. Report any discrepancies to the instructor.

Instructors or graders grade the assignment:
1. Suggestion: wait until after the deadline and grade all submissions in one pass.
2. Spot-check that the autograder results look reasonable (a mix of perfect, low, and in-between scores).
3. Use the [Code Similarity tool](https://help.gradescope.com/article/3vr6x46ppn-instructor-assignment-programming-code-similarity) to detect gross plagiarism and respond accordingly.
4. Perform manual grading (if applicable).
5. Click *Publish Grades* to push scores to Canvas.

After grading:
1. Students may request regrades through Gradescope.
2. Suggestion: ask students to request regrades only through Gradescope, not out-of-band. This makes it clear which question the student is inquiring about (which can be difficult to communicate), ensures that regrades do not slip through the cracks, and routes the request properly in the case of multiple graders.
3. After regrading in Gradescope, the instructor/grader needs to *Publish Grades* again to sync to Canvas.

## `grade.py` Scripts

Your assessment logic is defined in a `grade.py` script. The `make grade` make target compiles the code and then executes `grade.py`. Students will run `make grade` interactively on local machines, and the Gradescope autograder will run `make grade` in a headless container. When invoked by `make grade`, `grade.py` typically examines the submission code and executables; runs unit tests and examines their output (if using); prints a human-readable summary to standard output, for student consumption; and writes a `results.json`, for Gradescope autograder consumption.

There are two kinds of grading results:
- **Reject**: The submission is illegible or otherwise unacceptable. Examples: no names; identical to starter code; does not compile; unit tests crash. The score is a flat instructor-hardcoded number, often 0% or approximately 50%.
- **Accept**: The submission is acceptible, and grading proceeds. It is subjected to correctness tests, and each passing tests adds points to the score, counting up from zero.

See `gggg.py` for the high-level grading API.
- An `Assignment` object represents assignment policies, notably the maximum score, and score for a rejected submission.
- A `State` object represents the current state of the grading process, notably whether the submission has been rejected, and the total earned points.

Generally, a `grade.py` script will
1. `import` from `gggg`.
2. Create an `Assignment` and `State` object.
3. Call `State.reject_if...` functions to detect and reject where appropriate. These functions have no effect if the submission has already been rejected.
4. Call `State.gtest_run` to execute a unit test program. (Again, no effect if already rejected.)
5. Call `State...test` functions to evaluate whether to grant points. Each of these function calls corresponds to a rubric row. (Again, no effect if already rejected.)
6. Call `State.summarize()` to produce output. This step tells the student their score, and whether their submisison was rejected. So it needs to happen even if the submission was rejected.

The `template-example/grade.py` example contains:
```
from gggg import *

a = Assignment(12, 6)
s = State(a)

horizontal_rule()

s.reject_if_missing_contributors()
s.reject_if_starter_contributors()

s.reject_unless_files_exist(['product.hpp',
                             'product_test.cpp'])

s.reject_if_file_unchanged('product.hpp',
                           '953ed73434f4cae54b9161b48da2f25a2622522198a655c00de571bb596b16df')

s.reject_if_file_changed('product_test.cpp',
                         '0139691ee712697636a51e979b866b4a939f7840032fc81208f22c8931f90a5d')

s.reject_unless_command_succeeds(['make', 'clean', 'product_test'])

s.string_removed_test('TODO comments removed', 3, 'TODO', ['product.hpp'])

s.gtest_run('product_test')
s.gtest_suite_test('ProductPositive', 3)
s.gtest_suite_test('ProductZero', 3)
s.gtest_suite_test('ProductNegative', 3)

s.summarize()
```
## Testing Interactive Programs

Currently the only kind of correctness assessment that `gggg` supports is GoogleTest unit tests. This accommodates advanced computer science courses where students implement C++ modules with functions and class members. However, it does not accommodate introductory courses where students write programs that interact with stdin/stdout.

Functionality for running programs with stdin output and commandline arguments, and assessing stdout output and return codes, is planned for Spring 2022. The author will be teaching an introductory course in that time frame. We have legacy prototype code for this kind of assessment, and will refactor it into `gggg`.
