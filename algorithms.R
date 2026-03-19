# algorithms_base_r.R
# Base R implementations translated from pseudocode in the source file.
# No external libraries are used.

# ------------------------------------------------------------
# BASIC ALGORITHMS
# ------------------------------------------------------------

bubble_sort <- function(arr) {
  n <- length(arr)
  if (n <= 1) return(arr)
  for (i in 1:(n - 1)) {
    for (j in 1:(n - i)) {
      if (arr[j] > arr[j + 1]) {
        temp <- arr[j]
        arr[j] <- arr[j + 1]
        arr[j + 1] <- temp
      }
    }
  }
  arr
}

linear_search <- function(arr, target) {
  for (i in seq_along(arr)) {
    if (arr[i] == target) return(i)
  }
  -1
}

binary_search <- function(arr, target) {
  left <- 1
  right <- length(arr)
  while (left <= right) {
    mid <- floor((left + right) / 2)
    if (arr[mid] == target) {
      return(mid)
    } else if (arr[mid] < target) {
      left <- mid + 1
    } else {
      right <- mid - 1
    }
  }
  -1
}

factorial_rec <- function(n) {
  if (n <= 1) return(1)
  n * factorial_rec(n - 1)
}

fibonacci_rec <- function(n) {
  if (n <= 1) return(n)
  fibonacci_rec(n - 1) + fibonacci_rec(n - 2)
}

# ------------------------------------------------------------
# STRING ALGORITHMS
# ------------------------------------------------------------

compute_lps <- function(pattern) {
  m <- nchar(pattern)
  lps <- rep(0, m)
  len <- 0
  i <- 2

  while (i <= m) {
    if (substr(pattern, i, i) == substr(pattern, len + 1, len + 1)) {
      len <- len + 1
      lps[i] <- len
      i <- i + 1
    } else {
      if (len != 0) {
        len <- lps[len]
      } else {
        lps[i] <- 0
        i <- i + 1
      }
    }
  }
  lps
}

kmp_search <- function(text, pattern) {
  n <- nchar(text)
  m <- nchar(pattern)
  if (m == 0) return(integer(0))

  lps <- compute_lps(pattern)
  i <- 1
  j <- 1
  matches <- integer(0)

  while (i <= n) {
    if (substr(text, i, i) == substr(pattern, j, j)) {
      i <- i + 1
      j <- j + 1
    }

    if (j > m) {
      matches <- c(matches, i - j + 1)
      j <- lps[j - 1] + 1
    } else if (i <= n && substr(text, i, i) != substr(pattern, j, j)) {
      if (j != 1) {
        j <- lps[j - 1] + 1
      } else {
        i <- i + 1
      }
    }
  }

  matches
}

# ------------------------------------------------------------
# GRAPH ALGORITHMS
# Graph represented as adjacency matrix.
# 0 or Inf means no edge depending on function usage.
# ------------------------------------------------------------

dijkstra <- function(graph, start) {
  n <- nrow(graph)
  dist <- rep(Inf, n)
  prev <- rep(NA_integer_, n)
  visited <- rep(FALSE, n)

  dist[start] <- 0

  for (step in 1:n) {
    min_dist <- Inf
    u <- NA_integer_

    for (i in 1:n) {
      if (!visited[i] && dist[i] < min_dist) {
        min_dist <- dist[i]
        u <- i
      }
    }

    if (is.na(u)) break
    visited[u] <- TRUE

    for (v in 1:n) {
      w <- graph[u, v]
      if (!is.infinite(w) && w > 0 && !visited[v]) {
        alt <- dist[u] + w
        if (alt < dist[v]) {
          dist[v] <- alt
          prev[v] <- u
        }
      }
    }
  }

  list(distance = dist, previous = prev)
}

make_edges_from_matrix <- function(graph) {
  n <- nrow(graph)
  edges <- list()
  idx <- 1
  for (i in 1:(n - 1)) {
    for (j in (i + 1):n) {
      if (!is.infinite(graph[i, j]) && graph[i, j] > 0) {
        edges[[idx]] <- c(i, j, graph[i, j])
        idx <- idx + 1
      }
    }
  }
  if (length(edges) == 0) return(matrix(numeric(0), ncol = 3))
  do.call(rbind, edges)
}

find_set <- function(parent, x) {
  while (parent[x] != x) {
    x <- parent[x]
  }
  x
}

union_set <- function(parent, rank, x, y) {
  root_x <- find_set(parent, x)
  root_y <- find_set(parent, y)

  if (root_x == root_y) {
    return(list(parent = parent, rank = rank))
  }

  if (rank[root_x] < rank[root_y]) {
    parent[root_x] <- root_y
  } else if (rank[root_x] > rank[root_y]) {
    parent[root_y] <- root_x
  } else {
    parent[root_y] <- root_x
    rank[root_x] <- rank[root_x] + 1
  }

  list(parent = parent, rank = rank)
}

kruskal <- function(graph) {
  n <- nrow(graph)
  edges <- make_edges_from_matrix(graph)

  if (nrow(edges) == 0) {
    return(list(mst = matrix(numeric(0), ncol = 3), total_weight = 0))
  }

  edges <- edges[order(edges[, 3]), , drop = FALSE]
  parent <- 1:n
  rank <- rep(0, n)
  mst <- list()
  idx <- 1
  total_weight <- 0

  for (k in 1:nrow(edges)) {
    u <- edges[k, 1]
    v <- edges[k, 2]
    w <- edges[k, 3]

    if (find_set(parent, u) != find_set(parent, v)) {
      mst[[idx]] <- c(u, v, w)
      idx <- idx + 1
      total_weight <- total_weight + w
      merged <- union_set(parent, rank, u, v)
      parent <- merged$parent
      rank <- merged$rank
    }
  }

  mst_matrix <- if (length(mst) == 0) matrix(numeric(0), ncol = 3) else do.call(rbind, mst)
  list(mst = mst_matrix, total_weight = total_weight)
}

prim <- function(graph, start = 1) {
  n <- nrow(graph)
  selected <- rep(FALSE, n)
  selected[start] <- TRUE
  mst <- list()
  idx <- 1
  total_weight <- 0

  while (sum(selected) < n) {
    min_w <- Inf
    a <- NA_integer_
    b <- NA_integer_

    for (i in 1:n) {
      if (selected[i]) {
        for (j in 1:n) {
          if (!selected[j] && !is.infinite(graph[i, j]) && graph[i, j] > 0) {
            if (graph[i, j] < min_w) {
              min_w <- graph[i, j]
              a <- i
              b <- j
            }
          }
        }
      }
    }

    if (is.na(a) || is.na(b)) break

    mst[[idx]] <- c(a, b, min_w)
    idx <- idx + 1
    total_weight <- total_weight + min_w
    selected[b] <- TRUE
  }

  mst_matrix <- if (length(mst) == 0) matrix(numeric(0), ncol = 3) else do.call(rbind, mst)
  list(mst = mst_matrix, total_weight = total_weight)
}

# ------------------------------------------------------------
# MACHINE LEARNING - BASE R ONLY
# ------------------------------------------------------------

linear_regression_train <- function(X, Y) {
  x_mean <- mean(X)
  y_mean <- mean(Y)

  numerator <- sum((X - x_mean) * (Y - y_mean))
  denominator <- sum((X - x_mean)^2)

  slope <- numerator / denominator
  intercept <- y_mean - slope * x_mean

  list(slope = slope, intercept = intercept)
}

linear_regression_predict <- function(X, model) {
  model$slope * X + model$intercept
}

sigmoid <- function(z) {
  1 / (1 + exp(-z))
}

logistic_regression_train <- function(X, Y, lr = 0.01, epochs = 1000) {
  X <- as.matrix(X)
  n <- nrow(X)
  p <- ncol(X)
  w <- rep(0, p)
  b <- 0

  for (epoch in 1:epochs) {
    for (i in 1:n) {
      z <- sum(w * X[i, ]) + b
      p_hat <- sigmoid(z)
      error <- p_hat - Y[i]
      w <- w - lr * error * X[i, ]
      b <- b - lr * error
    }
  }

  list(weights = w, bias = b)
}

logistic_regression_predict <- function(X, model) {
  X <- as.matrix(X)
  probs <- rep(0, nrow(X))
  for (i in 1:nrow(X)) {
    probs[i] <- sigmoid(sum(model$weights * X[i, ]) + model$bias)
  }
  ifelse(probs >= 0.5, 1, 0)
}

distance_euclidean <- function(a, b) {
  sqrt(sum((a - b)^2))
}

kmeans_simple <- function(X, k, max_iter = 100) {
  X <- as.matrix(X)
  n <- nrow(X)

  centroids <- X[1:k, , drop = FALSE]
  clusters <- rep(0, n)

  for (iter in 1:max_iter) {
    old_clusters <- clusters

    for (i in 1:n) {
      dists <- rep(0, k)
      for (j in 1:k) {
        dists[j] <- distance_euclidean(X[i, ], centroids[j, ])
      }
      clusters[i] <- which.min(dists)
    }

    for (j in 1:k) {
      members <- X[clusters == j, , drop = FALSE]
      if (nrow(members) > 0) {
        centroids[j, ] <- colMeans(members)
      }
    }

    if (all(old_clusters == clusters)) break
  }

  list(clusters = clusters, centroids = centroids)
}

svm_train_simple <- function(X, Y, learning_rate = 0.001, epochs = 1000, lambda = 0.01) {
  X <- as.matrix(X)
  n <- nrow(X)
  p <- ncol(X)
  w <- rep(0, p)
  b <- 0

  for (epoch in 1:epochs) {
    for (i in 1:n) {
      condition <- Y[i] * (sum(w * X[i, ]) + b)
      if (condition < 1) {
        w <- w + learning_rate * (Y[i] * X[i, ] - 2 * lambda * w)
        b <- b + learning_rate * Y[i]
      } else {
        w <- w - learning_rate * 2 * lambda * w
      }
    }
  }

  list(weights = w, bias = b)
}

svm_predict_simple <- function(X, model) {
  X <- as.matrix(X)
  preds <- rep(0, nrow(X))
  for (i in 1:nrow(X)) {
    score <- sum(model$weights * X[i, ]) + model$bias
    preds[i] <- ifelse(score >= 0, 1, -1)
  }
  preds
}

naive_bayes_train_binary <- function(X, Y) {
  X <- as.matrix(X)
  classes <- sort(unique(Y))
  model <- list()
  model$classes <- classes
  model$priors <- numeric(length(classes))
  model$feature_probs <- vector("list", length(classes))

  for (ci in seq_along(classes)) {
    cls <- classes[ci]
    Xc <- X[Y == cls, , drop = FALSE]
    model$priors[ci] <- nrow(Xc) / nrow(X)

    probs <- rep(0, ncol(X))
    for (j in 1:ncol(X)) {
      probs[j] <- (sum(Xc[, j] == 1) + 1) / (nrow(Xc) + 2)
    }
    model$feature_probs[[ci]] <- probs
  }

  model
}

naive_bayes_predict_binary <- function(X, model) {
  X <- as.matrix(X)
  preds <- rep(NA, nrow(X))

  for (i in 1:nrow(X)) {
    scores <- rep(0, length(model$classes))
    for (ci in seq_along(model$classes)) {
      probs <- model$feature_probs[[ci]]
      log_prob <- log(model$priors[ci])
      for (j in 1:ncol(X)) {
        if (X[i, j] == 1) {
          log_prob <- log_prob + log(probs[j])
        } else {
          log_prob <- log_prob + log(1 - probs[j])
        }
      }
      scores[ci] <- log_prob
    }
    preds[i] <- model$classes[which.max(scores)]
  }

  preds
}

# ------------------------------------------------------------
# APRIORI
# Transactions are character vectors inside a list.
# ------------------------------------------------------------

all_items <- function(transactions) {
  sort(unique(unlist(transactions)))
}

count_occurrences <- function(item, transactions) {
  count <- 0
  for (tx in transactions) {
    if (item %in% tx) count <- count + 1
  }
  count
}

generate_candidates <- function(prev_itemsets, k) {
  candidates <- list()
  idx <- 1

  if (length(prev_itemsets) == 0) return(candidates)

  for (i in 1:length(prev_itemsets)) {
    for (j in 1:length(prev_itemsets)) {
      union_set_items <- sort(unique(c(prev_itemsets[[i]], prev_itemsets[[j]])))
      if (length(union_set_items) == k) {
        key <- paste(union_set_items, collapse = ",")
        exists <- FALSE
        if (length(candidates) > 0) {
          for (cand in candidates) {
            if (paste(cand, collapse = ",") == key) {
              exists <- TRUE
              break
            }
          }
        }
        if (!exists) {
          candidates[[idx]] <- union_set_items
          idx <- idx + 1
        }
      }
    }
  }

  candidates
}

apriori <- function(transactions, min_support = 0.5) {
  freq_itemsets <- list()

  one_itemsets <- list()
  items <- all_items(transactions)

  for (item in items) {
    count <- count_occurrences(item, transactions)
    if ((count / length(transactions)) >= min_support) {
      key <- item
      freq_itemsets[[key]] <- count
      one_itemsets[[length(one_itemsets) + 1]] <- c(item)
    }
  }

  current_frequent_itemsets <- one_itemsets
  k <- 2

  while (length(current_frequent_itemsets) > 0) {
    candidates <- generate_candidates(current_frequent_itemsets, k)
    candidate_counts <- list()

    for (candidate in candidates) {
      count <- 0
      for (transaction in transactions) {
        if (all(candidate %in% transaction)) {
          count <- count + 1
        }
      }
      key <- paste(candidate, collapse = ",")
      candidate_counts[[key]] <- count
    }

    next_frequent <- list()
    for (name in names(candidate_counts)) {
      count <- candidate_counts[[name]]
      if ((count / length(transactions)) >= min_support) {
        items_vec <- unlist(strsplit(name, ",", fixed = TRUE))
        next_frequent[[length(next_frequent) + 1]] <- items_vec
        freq_itemsets[[name]] <- count
      }
    }

    current_frequent_itemsets <- next_frequent
    k <- k + 1
  }

  freq_itemsets
}

# ------------------------------------------------------------
# SIMPLE DECISION STUMP + GRADIENT BOOSTING FOR REGRESSION
# ------------------------------------------------------------

train_weak_learner <- function(X, target) {
  X <- as.numeric(X)
  target <- as.numeric(target)

  sorted_x <- sort(unique(X))
  if (length(sorted_x) == 1) {
    return(list(threshold = sorted_x[1], left_value = mean(target), right_value = mean(target)))
  }

  best_sse <- Inf
  best_model <- NULL

  for (threshold in sorted_x) {
    left_idx <- X <= threshold
    right_idx <- X > threshold

    if (sum(left_idx) == 0 || sum(right_idx) == 0) next

    left_value <- mean(target[left_idx])
    right_value <- mean(target[right_idx])

    preds <- ifelse(X <= threshold, left_value, right_value)
    sse <- sum((target - preds)^2)

    if (sse < best_sse) {
      best_sse <- sse
      best_model <- list(threshold = threshold, left_value = left_value, right_value = right_value)
    }
  }

  if (is.null(best_model)) {
    best_model <- list(threshold = mean(X), left_value = mean(target), right_value = mean(target))
  }

  best_model
}

predict_tree <- function(tree, X_new) {
  X_new <- as.numeric(X_new)
  ifelse(X_new <= tree$threshold, tree$left_value, tree$right_value)
}

gradient_boosting_train <- function(X, Y, num_trees = 10, learning_rate = 0.1) {
  X <- as.numeric(X)
  Y <- as.numeric(Y)

  F <- rep(mean(Y), length(Y))
  trees <- vector("list", num_trees)

  for (m in 1:num_trees) {
    residuals <- Y - F
    tree <- train_weak_learner(X, residuals)
    trees[[m]] <- tree
    predictions <- predict_tree(tree, X)
    F <- F + learning_rate * predictions
  }

  list(base_value = mean(Y), trees = trees, learning_rate = learning_rate)
}

gradient_boosting_predict <- function(model, X_new) {
  X_new <- as.numeric(X_new)
  F_pred <- rep(model$base_value, length(X_new))
  for (tree in model$trees) {
    F_pred <- F_pred + model$learning_rate * predict_tree(tree, X_new)
  }
  F_pred
}

# ------------------------------------------------------------
# DEMO
# ------------------------------------------------------------

demo_run <- function() {
  cat("Bubble sort:\n")
  arr <- c(5, 2, 9, 1, 3)
  print(bubble_sort(arr))

  cat("\nLinear search for 9:\n")
  print(linear_search(arr, 9))

  cat("\nBinary search for 5 in sorted array:\n")
  sorted_arr <- bubble_sort(arr)
  print(binary_search(sorted_arr, 5))

  cat("\nFactorial 5:\n")
  print(factorial_rec(5))

  cat("\nFibonacci 6:\n")
  print(fibonacci_rec(6))

  cat("\nKMP search:\n")
  print(kmp_search("ababcabcabababd", "ababd"))

  cat("\nLinear regression:\n")
  X <- c(1, 2, 3, 4, 5)
  Y <- c(2, 4, 5, 4, 5)
  lm_model <- linear_regression_train(X, Y)
  print(lm_model)
  print(linear_regression_predict(X, lm_model))

  cat("\nApriori:\n")
  transactions <- list(
    c("A", "B", "C"),
    c("A", "C"),
    c("A", "B"),
    c("B", "C"),
    c("A", "B", "C")
  )
  print(apriori(transactions, min_support = 0.4))
}

if (sys.nframe() == 0) {
  demo_run()
}
