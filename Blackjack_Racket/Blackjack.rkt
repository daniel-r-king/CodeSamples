#lang racket

(define faces '(2 3 4 5 6 7 8 9 10 J Q K A))

(define suits '(Clubs Diamonds Hearts Spades))

;make-deck builds a 52-card unshuffled deck 
(define (make-deck)
  ;build-suit constructs a set containing one card of each face value in a given suit
  (letrec ([build-suit
            (lambda (face suit cards counter)
              (cond [(= counter 13)
                     cards
                     ]
                    [else
                     (set! cards (cons (cons (car face) (car suit)) cards))
                     (build-suit (cdr face) suit cards (+ counter 1))
                     ])
              )
            ])
    ;build-deck uses build-suit to construct a complete deck consisting of one card for each face value and suit
    (letrec ([build-deck
              (lambda (suits deck counter)
                (cond [(= counter 4)
                       deck
                       ]
                      [else
                       (set! deck (append deck (build-suit faces suits '() 0)))
                       (build-deck (cdr suits) deck (+ counter 1))
                       ])
                )
              ])
      ;seed call stack
      (build-deck suits '() 0)
      )
    )
  )

;eval-hand scores a Blackjack hand
(define (eval-hand hand)
  ;score checks a card's point value and adds it to an accumulator, unless that card is an ace
  (letrec ([score
            (lambda (hand acc aces)
              (cond [(null? hand)
                     ;score-aces takes the previously accumulated score from the rest of the hand,
                     ;decides how to score the aces, and returns the final score
                     (letrec ([score-aces
                               (lambda (acc aces)
                                 (cond [(null? aces)
                                        acc
                                        ]
                                       [(> acc 10)
                                        (score-aces (+ 1 acc) (cdr aces))
                                        ]
                                       [else
                                        (score-aces (+ 11 acc) (cdr aces))
                                        ])
                                 )
                               ])
                       (score-aces acc aces)
                       )
                     ]
                    [(or
                      (equal? (car (car hand)) 'J)
                      (equal? (car (car hand)) 'Q)
                      (equal? (car (car hand)) 'K))
                     (score (cdr hand) (+ acc 10) aces)
                     ]
                    ;if the currently processing card is an ace, add it to a separate collection
                    [(equal? (car (car hand)) 'A)
                     (set! aces (append aces (list (car hand))))
                     (score (cdr hand) acc aces)
                     ]
                    [else
                     (score (cdr hand) (+ acc (car (car hand))) aces)
                     ]
                    )
              )
            ])
    (score (unbox hand) 0 '())
    )
  )

;deal! takes two cards from the top of a deck and adds them to a hand
(define (deal! deck)
  (letrec ([build-hand
            (lambda (hand deck counter)
              (cond [(= counter 2)
                     hand
                     ]
                    [else
                     (set! hand (cons (car (unbox deck)) hand))
                     (set-box! deck (cdr (unbox deck)))
                     (build-hand hand deck (+ counter 1))
                     ])
              )
            ])
    (build-hand '() deck 0)
    )
  )

;hit! removes one card from the top of the deck and adds them to a hand
(define (hit! hand deck)
  (set-box! hand (append (unbox hand) (list (car (unbox deck)))))
  (set-box! deck (cdr (unbox deck)))
  )

(define (show-hand hand how description)
  (cond [(equal? how 'Part)
         (display description)
         (newline)
         (display "***** ")
         (display (cdr (unbox hand)))
         ]
        [(equal? how 'Full)
         (display description)
         (newline)
         (display (unbox hand))
         ])
  )

;shuffle shuffles a set of cards
(define (shuffle cards)
  (sort (unbox cards) (lambda (x y) (< 0.5 (random))))
  )

;show-menu displays a UI menu
(define (show-menu)
  (newline)
  (display "Menu:")
  (newline)
  (display "1. Start a new hand.")
  (newline)
  (display "2. Hit.")
  (newline)
  (display "3. Stay.")
  (newline)
  (display "4. Bet.")
  (newline)
  )

;The following block runs the game using the functions declared above. Dealer will hit until
;until the total score of his cards reaches 17. You will begin with $100 and may bet any amount
;at any time. If you win, you will receive %150 of your original wager as a prize. If you lose,
;you forfeit your wager. If the game is a draw, you will be refunded your wager.
(let ([deck (box (make-deck))] [dhand (box '())] [uhand (box '())] [bank 100] [wager 0])
  (display "Welcome to Blackjack!")
  (show-menu)
  (let loop ()
    (display "Enter a number <1-4>: ")
    (define inputReceived (read-line (current-input-port) 'any))
    (cond [(equal? inputReceived "1")
           (set-box! deck (shuffle deck))
           (set-box! uhand (deal! deck))
           (set-box! dhand (deal! deck))
           (newline)
           (show-hand uhand 'Full "Your hand: ")
           (newline)
           (show-hand dhand 'Part "Dealer's hand: ")
           (newline)
           ]
          [(equal? inputReceived "2")
           (cond [(null? (unbox uhand))
                  (display "You don't have a hand!")
                  ]
                 [else
                  (hit! uhand deck)
                  (cond [(< (eval-hand dhand) 17)
                         (hit! dhand deck)
                         ])
                  (newline)
                  (show-hand uhand 'Full "Your hand: ")
                  (newline)
                  (show-hand dhand 'Part "Dealer's hand: ")
                  (newline)
                  ])
           ]
          [(equal? inputReceived "3")
           (letrec ([dealer-play
                     (lambda (hand)
                       (cond [(> (eval-hand dhand) 17)
                              dhand
                              ]
                             [else
                              (hit! dhand deck)])
                       )
                     ])
             (dealer-play dhand)
             )
           (let ([uscore (eval-hand uhand)] [dscore (eval-hand dhand)])
             (cond [(> uscore 21)
                    (newline)
                    (show-hand uhand 'Full "Your hand: ")
                    (newline)
                    (show-hand dhand 'Full "Dealer's hand: ")
                    (newline)
                    (display "SCORE: ")
                    (display uscore)
                    (display " - ")
                    (display dscore)
                    (newline)
                    (newline)
                    (display "YOU LOSE!!!")
                    (set-box! deck (shuffle (box (make-deck))))
                    (set-box! uhand '())
                    (set-box! dhand '())
                    (newline)
                    (display "-$")
                    (display wager)
                    (newline)
                    (display "Bank: $")
                    (display bank)
                    (set! wager 0)
                    (newline)
                    (show-menu)
                    ]
                   [(and (> dscore 21) (< uscore 22))
                    (newline)
                    (show-hand uhand 'Full "Your hand: ")
                    (newline)
                    (show-hand dhand 'Full "Dealer's hand: ")
                    (newline)
                    (display "SCORE: ")
                    (display uscore)
                    (display " - ")
                    (display dscore)
                    (newline)
                    (newline)
                    (display "YOU WIN!!!")
                    (set-box! deck (shuffle (box (make-deck))))
                    (set-box! uhand '())
                    (set-box! dhand '())
                    (newline)
                    (set! bank (+ bank (* wager 1.5)))
                    (display "+$")
                    (display (* wager 1.5))
                    (newline)
                    (display "Bank: ")
                    (display bank)
                    (set! wager 0)
                    (newline)
                    (show-menu)
                    ]
                   [(and (> uscore dscore) (< uscore 22))
                    (newline)
                    (show-hand uhand 'Full "Your hand: ")
                    (newline)
                    (show-hand dhand 'Full "Dealer's hand: ")
                    (newline)
                    (display "SCORE: ")
                    (display uscore)
                    (display " - ")
                    (display dscore)
                    (newline)
                    (newline)
                    (display "YOU WIN!!!")
                    (set-box! deck (shuffle (box (make-deck))))
                    (set-box! uhand '())
                    (set-box! dhand '())
                    (newline)
                    (set! bank (+ bank (* wager 1.5)))
                    (display "+$")
                    (display (* wager 1.5))
                    (newline)
                    (display "Bank: $")
                    (display bank)
                    (set! wager 0)
                    (newline)
                    (show-menu)
                    ]
                   [(and (> dscore uscore) (< dscore 22))
                    (newline)
                    (show-hand uhand 'Full "Your hand: ")
                    (newline)
                    (show-hand dhand 'Full "Dealer's hand: ")
                    (newline)
                    (display "SCORE: ")
                    (display uscore)
                    (display " - ")
                    (display dscore)
                    (newline)
                    (newline)
                    (display "YOU LOSE!!!")
                    (set-box! deck (shuffle (box (make-deck))))
                    (set-box! uhand '())
                    (set-box! dhand '())
                    (newline)
                    (display "-$")
                    (display wager)
                    (newline)
                    (display "Bank: $")
                    (display bank)
                    (set! wager 0)
                    (newline)
                    (show-menu)
                    ]
                   [else
                    (newline)
                    (show-hand uhand 'Full "Your hand: ")
                    (newline)
                    (show-hand dhand 'Full "Dealer's hand: ")
                    (newline)
                    (display "SCORE: ")
                    (display uscore)
                    (display " - ")
                    (display dscore)
                    (newline)
                    (newline)
                    (display "Draw!")
                    (set-box! deck (shuffle (box (make-deck))))
                    (set-box! uhand '())
                    (set-box! dhand '())
                    (newline)
                    (set! bank (+ bank wager))
                    (display "+$")
                    (display wager)
                    (newline)
                    (display "Bank: $")
                    (display bank)
                    (newline)
                    (show-menu)
                    ]
                   )
             )
           ]
          [(equal? inputReceived "4")
           (display "Enter your wager: ")
           (define wagerReceived (read-line (current-input-port) 'any))
           (set! bank (- bank (string->number wagerReceived)))
           (set! wager (string->number wagerReceived))
           (display "Wager set at $")
           (display wager)
           ]
          )
    (newline)
    (loop))
  )