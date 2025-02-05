

SELECT *
FROM ( SELECT FO.PRODUCT_ID, FP.PRODUCT_NAME, SUM(FO.AMOUNT * FP.PRICE) AS TOTAL_SALES
      FROM
        (SELECT *
        FROM FOOD_ORDER
        WHERE PRODUCE_DATE BETWEEN '2022-05-01' AND '2022-05-31') AS FO
             JOIN 
        FOOD_PRODUCT AS FP
        ON FO.PRODUCT_ID = FP.PRODUCT_ID
      GROUP BY FO.PRODUCT_ID
) AS RES
ORDER BY TOTAL_SALES DESC, RES.PRODUCT_ID