(*
  OCaml (Functional): Mean, Median, Mode for a list of integers.
  - Reads one line of space-separated integers from stdin.
  - Uses immutable lists and list operations (map/fold/sort).
  - Computes mean, median, and mode (prints "None" if no value repeats).
*)

let read_int_list () : int list option =
  let line = read_line () in
  let tokens =
    line
    |> String.trim
    |> String.split_on_char ' '
    |> List.filter (fun s -> s <> "")
  in
  if tokens = [] then None
  else
    try
      Some (List.map int_of_string tokens)
    with Failure _ ->
      None

let mean (xs : int list) : float =
  let sum = List.fold_left ( + ) 0 xs in
  let n = List.length xs in
  float_of_int sum /. float_of_int n

let median_after_sort (sorted : int list) : float =
  let n = List.length sorted in
  if n mod 2 = 1 then
    float_of_int (List.nth sorted (n / 2))
  else
    let a = List.nth sorted (n / 2 - 1) in
    let b = List.nth sorted (n / 2) in
    (float_of_int a +. float_of_int b) /. 2.0

(*
  Mode calculation:
  - Sorting groups equal values together.
  - Build run-length counts: (value, frequency) list.
  - Find maximum frequency; if it is 1, there is no mode.
  - Otherwise return all values whose frequency equals the maximum.
*)
let modes_after_sort (sorted : int list) : int list =
  let counts =
    sorted
    |> List.fold_left
         (fun acc x ->
           match acc with
           | (v, c) :: rest when v = x -> (v, c + 1) :: rest
           | _ -> (x, 1) :: acc)
         []
    |> List.rev
  in
  let max_freq =
    counts
    |> List.fold_left (fun m (_, c) -> if c > m then c else m) 1
  in
  if max_freq = 1 then []
  else
    counts
    |> List.filter (fun (_, c) -> c = max_freq)
    |> List.map fst

let () =
  print_endline "Enter integers separated by spaces:";

  match read_int_list () with
  | None ->
      print_endline "Error: please enter at least one integer."
  | Some xs ->
      let sorted = List.sort compare xs in
      let mu = mean xs in
      let med = median_after_sort sorted in
      let ms = modes_after_sort sorted in

      Printf.printf "Count: %d\n" (List.length xs);
      Printf.printf "Mean: %.2f\n" mu;

      (* Print median as integer if whole; otherwise with 2 decimals *)
      if med = float_of_int (int_of_float med) then
        Printf.printf "Median: %d\n" (int_of_float med)
      else
        Printf.printf "Median: %.2f\n" med;

      (match ms with
       | [] -> print_endline "Mode: None"
       | _  ->
           Printf.printf "Mode:";
           List.iter (fun v -> Printf.printf " %d" v) ms;
           print_newline ())
